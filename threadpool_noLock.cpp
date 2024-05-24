#include<fstream>
#include<iostream>
#include<string.h>
#include<vector>
#include<thread>
#include<mutex>

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
    float min_val, max_val, total_sum;
    int count = 0;

    hashnode(){}
    hashnode(char * c, int l){
        memcpy(this->city, c, l + 1);
        this->len = l;
    }
    void node_insert(float value){
        if(this->count == 0){
            this->count = 1;
            this->min_val = this->max_val = this->total_sum = value;
        }
        else{
            this->count++;
            this->min_val = ((this->min_val > value) ? value : this->min_val);
            this->max_val = ((this->max_val < value) ? value : this->max_val);
            this->total_sum += value;
        }
        // cout<<total_sum<<endl;
    }
    void final_insert(float minval, float maxval, float totalval, float countval){
        if(count == 0){
            min_val = minval;
            max_val = maxval;
        }
        else{
            min_val = ((min_val > minval) ? minval : min_val);
            max_val = ((max_val < maxval) ? maxval : max_val);
        }
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


void process(hashmap & res, streampos start_file_ptr, streampos end_file_ptr, int thread_id){

    // hashmap res = hashmap();
    // int num_of_iterations = 5e4;
    // int chunk_size = (end_file_ptr - start_file_ptr + num_of_iterations - 1) / num_of_iterations;
    int chunk_size = 1e6;

    char chunk[chunk_size + 30];
    int chunk_max_len = chunk_size + 30;
    int count = 0;
    int chunk_len = 0;
    ifstream file("measurements.txt", ios::binary);
    file.seekg(start_file_ptr);
    end_file_ptr -= 1;

    while(start_file_ptr < end_file_ptr){
        int temp_chunk_size = ((end_file_ptr - start_file_ptr) > chunk_size ? chunk_size : (end_file_ptr - start_file_ptr) );
        // debug.lock();
        // cout<<"Thread ID :- "<<thread_id<<" "<<file.tellg()<<" ";
        // cout<<start_file_ptr<<" ";
        // cout<<start_file_ptr + temp_chunk_size<<endl;
        // debug.unlock();
        read_chunk(file, chunk, chunk_max_len, temp_chunk_size, chunk_len);
        start_file_ptr += chunk_len;
        char line[50];
        int line_length = 0;
        char city[50];
        int city_len;
        float fval;
        int ival;
        
        // fetching city name and value from each line
        for(int i = 0; i < chunk_len && chunk[i] != '\0'; i++){
            if(chunk[i] == ';'){
            line[line_length] = '\0';
            memcpy(city, line, line_length + 1);
            city_len = line_length;
            line_length = 0;
            // cout<<city<<" ";
            }
            else if(chunk[i] == '\n'){
            line[line_length] = '\0';

            // basically custom atof for this code
            fval = 0;
            float tmp = 1;
            for(int j = line_length - 1; j >= 0 && line[j] != '.'; j--){
                tmp /= 10;
            }
            for(int j = line_length - 1; j >= 0; j--){
                if(line[j] == '.'){
                continue;
                }
                else if(line[j] == '-'){
                fval *= -1;
                }
                else{
                fval += (tmp * (line[j] - '0'));
                tmp *= 10;
                }
            }
            // insert(res, city, city_len, fval);
            // debug.lock();
            // cout<<"Thread "<<thread_id<<":- ";
            res.hash_insert(city, city_len, fval);
            // debug.unlock();
            line_length = 0;
            count++;
            }
            else{
            line[line_length] = chunk[i];
            line_length++;
            }
        }
        // count++;
      // if(count == 700){
      //   break;
      // }
    }

    // for(auto i : res){
    //   cout<<i.first.city<<" "<<i.second[0]<<" "<<i.second[1]<<" "<<i.second[2]<<" "<<i.second[3]<<endl;
    // }

    // long long int total_count = 0;
    // for(int i = 0; i < (10000); i++){
    //   if(res.hashtable[i] != -1){
    //     cout<<res.ht2[i].city<<" "<<res.ht2[i].min_val<<" "<<res.ht2[i].max_val<<" "<<res.ht2[i].total_sum<<" "<<res.ht2[i].count<<endl;
    //     total_count += res.ht2[i].count;
    //   }
    // }

    // cout<<total_count<<endl;
}

int main(){
    ifstream file = ifstream("measurements.txt", ios::binary);
    // char chunk[100000];
    // int chunk_size = 100000;
    // char chunk[chunk_size + 30];
    file.seekg(0, file.end);
    long long int length = file.tellg();
    file.clear();
    file.seekg(0, file.beg);
    streampos file_ptr = file.tellg();
    streampos prev_file_ptr;
    int num_threads = 4;

    hashmap res[num_threads];
    vector<thread> threads_vector;

    // int chunk_len = 0;
    long long int chunk_size = (length + num_threads - 1) / num_threads;
    for(int i = 0; i < num_threads; i++){
        // read_chunk(chunk, chunk_size, chunk_len);
        res[i] = hashmap();
        prev_file_ptr = file.tellg();
        file_ptr += chunk_size - 1;
        file.seekg(file_ptr);
        char buffer = '\0';
        // file.read(&buffer, 1);
        while(buffer != '\n' && file.read(&buffer, 1)){
            file_ptr+=1;
        }
        if(file.tellg() == -1){
            file_ptr = length + 1;
        }

        threads_vector.emplace_back(thread(process, ref(res[i]), prev_file_ptr, file_ptr, i));
        // debug.lock();
        // cout<<prev_file_ptr<<" "<<file_ptr<<endl;
        // debug.unlock();
        // cout<<file.tellg()<<" "<<file_ptr<<endl;
        // read_chunk(chunk, chunk_size, chunk_len);
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

    // file.seekg(file_ptr);
    // file.read(chunk, 1);

    // cout<<file.tellg()<<endl;


    return 0;
}