#include<fstream>
#include<iostream>
#include<string.h>
#include<vector>
#include<thread>
#include<mutex>
#include<sys/mman.h>
#include<fcntl.h>
#include<unistd.h>

using namespace std;

// ifstream file;
mutex debug;

void read_chunk(ifstream & file, char *chunk, int chunk_max_len, size_t chunk_size, int &chunk_len){
    memset(chunk, '\0', chunk_max_len);
    file.read(chunk, chunk_size);

    char buffer = chunk[chunk_size - 1];
    while(buffer != '\n' && file.read(&buffer, 1)){
        chunk[chunk_size] = buffer;
        chunk_size++;
    }
    chunk[chunk_size] = '\0';
    chunk_len = chunk_size;
}

struct hashnode{
    char city[50] = "\0";
    int len = 0;
    int min_val = 1000;
    int max_val = -1000;
    long long int total_sum;
    int count = 0;

    hashnode(){}
    hashnode(char * c, int l){
        memcpy(this->city, c, l + 1);
        this->len = l;
        // city[len] = '\0';
    }
    void node_insert(int value){
        this->count++;
        this->min_val = ((this->min_val > value) ? value : this->min_val);
        this->max_val = ((this->max_val < value) ? value : this->max_val);
        this->total_sum += value;
        // cout<<total_sum<<endl;
    }
    void final_insert(int minval, int maxval, int totalval, int countval){
        min_val = ((min_val > minval) ? minval : min_val);
        max_val = ((max_val < maxval) ? maxval : max_val);
        total_sum += totalval;
        count += countval;
    }
};

struct hashmap{
    int max_size = 10000;
    int hashtable[10000];
    hashnode ht2[10000];
    
    hashmap(){
        memset(this->hashtable, -1, this->max_size*sizeof(int));
    }
    void hash_insert(char * city, int len, float value){
        // hashfunction to create int out of string
        // int index = fnv1a_hashfunc(city, len);
        int index = hashfunc(city, len);
        // cout<<index<<endl;
        // linear probing
        // checking from hashtable if it contains value then checking if it's the same city as given in arg
        while(hashtable[index] != -1 && (len != ht2[index].len || (memcmp(ht2[index].city, city, len) != 0))){
            index++;
            index %= this->max_size;
        }
        if(hashtable[index] == -1){
            ht2[index] = hashnode(city, len);
            hashtable[index] = 1;
        }
        ht2[index].node_insert(value);
    }

    unsigned int hashfunc(char * city, int len){
        return ((city[0]<<14) | (city[len - 1]<<6) | len) % this->max_size;
    }
    // 13 bit fnv1a hash function
    // http://www.isthe.com/chongo/tech/comp/fnv/
    unsigned int fnv1a_hashfunc(char * city, int len){
        unsigned const int fnv_prime = 0x01000193;
        unsigned const int mask = ((1<<13) - 1);
        unsigned int hash = 0x811C9DC5;
        for(int i = 0; i < len; i++){
            hash ^= city[i];
            hash *= fnv_prime;
        }

        hash = ((hash >> 13) ^ (hash & mask)) % max_size;

        return hash;
    }
    void final_hash_insert(char * city, float len, float minval, float maxval, float totalval, float countval){
        // int index = fnv1a_hashfunc(city, len);
        int index = hashfunc(city, len);
        while(hashtable[index] != -1 && (len != ht2[index].len || (memcmp(ht2[index].city, city, len) != 0))){
            index++;
            index %= max_size;
        }
        if(hashtable[index] == -1){
            ht2[index] = hashnode(city, len);
            hashtable[index] = 1;
        }
        ht2[index].final_insert(minval, maxval, totalval, countval);
    }
};


void process(hashmap & res, char * chunk, long long int len, int thread_id){

    char city[50];
    int fval;
    int city_len;

    for(long long int i = 0; i < len; i++){
        if(chunk[i] == '\n'){
            fval = 0;
            city_len = 0;
            int tmp = 1;
            long long int j = i;
            for(j = i; j >= 0 && chunk[j] != ';'; j--){
                if(chunk[j] == '.') continue;
                else if(chunk[j] == '-'){
                    fval *= -1;
                }
                else{
                    fval += (tmp*(chunk[j] - '0'));
                    tmp *= 10;
                }
            }
            // fval *= 0.1;
            while(j >= 0 && chunk[j] != '\n')
                j--;
            j++;
            for(j; j >= 0 && chunk[j] != ';'; j++){
                city[city_len] = chunk[j];
                city_len++;
            }
            city[city_len] = '\0';

            res.hash_insert(city, city_len, fval);
        }
    }

}

int main(){
    
    int fd = open("measurements.txt", O_RDONLY);
    if (fd == -1) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    // Get the file size
    size_t size = lseek(fd, 0, SEEK_END);
    // size_t size = 700e6;
    // cout<<size<<endl;

    // Create a memory map of the file
    char* data = (char*)mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        cerr << "Error creating memory map" << endl;
        perror("mmap");
        return 1;
    }
    long long int length = size;
    int num_threads = 3;

    hashmap res[num_threads];
    vector<thread> threads_vector;

    long long int chunk_size = size / num_threads;
    long long int breakpoint = 0;
    for(int i = 0; i < num_threads; i++){
        res[i] = hashmap();

        // breakpoint += chunk_size;
        long long int temp_chunk_size = chunk_size;
        while(breakpoint + temp_chunk_size < size && data[breakpoint + temp_chunk_size] != '\n'){
            // cout<<data[breakpoint]<<" ";
            // breakpoint++;
            temp_chunk_size++;
        }
        if(temp_chunk_size + breakpoint > size){
            temp_chunk_size = size - breakpoint;
        }
        

        threads_vector.emplace_back(thread(process, ref(res[i]), data + breakpoint, temp_chunk_size + 1, i));
        breakpoint += temp_chunk_size + 1;
        // if(breakpoint > size){
        //     breakpoint = size;
        // }
        // cout<<temp_chunk_size<<" "<<breakpoint<<endl;
    }

    for(int i = 0; i < num_threads; i++){
        threads_vector[i].join();
    }

    hashmap final_res = hashmap();

    long long int total_count = 0;
    // for(int i = 0 ; i < num_cities; i++){
    //   cout<<final_cities[i]<<" "<<final_results[i][0]<<" "<<final_results[i][1]<<" "<<final_results[i][2]<<" "<<final_results[i][3]<<endl;
    //   total_count += (int) final_results[i][3];
    // }
    for(int i = 0; i < num_threads; i++){
      for(int j = 0; j < res[i].max_size; j++){
        if(res[i].hashtable[j] != -1){
          hashnode tmp = res[i].ht2[j];
          // cout<<tmp.city<<" "<<tmp.min_val<<" "<<tmp.max_val<<" "<<tmp.total_sum<<" "<<tmp.count<<endl;
          // total_count += tmp.count;
          final_res.final_hash_insert(tmp.city, tmp.len, tmp.min_val, tmp.max_val, tmp.total_sum, tmp.count);
        }
      }
      // cout<<endl;
    }


    for(int i = 0; i < final_res.max_size; i++){
      if(final_res.hashtable[i] != -1){
        hashnode tmp = final_res.ht2[i];
        cout<<tmp.city<<" "<<tmp.min_val<<" "<<tmp.max_val<<" "<<tmp.total_sum<<" "<<tmp.count<<endl;
        total_count += tmp.count;
      }
    }

    cout<<total_count<<endl;

    return 0;
}