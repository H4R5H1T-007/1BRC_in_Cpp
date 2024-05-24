#include<iostream>
#include<fstream>
// #include<map>
// #include<unordered_map>
#include<vector>
#include<string.h>

using namespace std;

ifstream file;

void read_chunk(char *chunk, size_t chunk_size, int &chunk_len){
    memset(chunk, '\0', chunk_size);
    file.read(chunk, chunk_size);

    char buffer = chunk[chunk_size - 1];
    while(buffer != '\n' && file.read(&buffer, 1)){
        chunk[chunk_size] = buffer;
        chunk_size++;
    }
    chunk[chunk_size] = '\0';
    chunk_len = chunk_size;
}

// struct char_struct{
//   char city[50] = "\0";
//   int len = 0;
  
//   char_struct(){}
//   char_struct(char* c, int l){
//     memcpy(this->city, c, l + 1);
//     this->len = l;
//   }

//   bool operator==(const char_struct& a) const
//   {
//     if(a.len != this->len){
//       return 0;
//     }
//     const int rc = memcmp(this->city, a.city, len);
//     if(rc == 0)
//       return 1;
    
//     return 0;
//   }
//   struct custom_hash {
//     size_t operator()(const char_struct & key) const {

//       return (((key.city[0] - 'A') << 24) + ((key.city[1] - 'A') << 16) + ((key.city[key.len - 2] - 'A') << 8) + ((key.city[key.len - 1] - 'A')));

//     }
//   };
  
// };

// void insert(unordered_map< char_struct, vector<float>, char_struct::custom_hash> & res, char *city, int len, float value){
//   vector<float>* tmp = &res[char_struct(city, len)];
//   if((*tmp).size() == 0){
//     (*tmp) = {value, value, value, 1};
//   }
//   else{
//     if((*tmp)[0] > value) (*tmp)[0] = value;
//     if((*tmp)[1] < value) (*tmp)[1] = value;
//     (*tmp)[2] += value;
//     (*tmp)[3]++;
//   }
// }

// void insert(hashmap & res, char * city, int len, float value){
//   res.hash_insert(city, len, value);
// }

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
    int index = fnv1a_hashfunc(city, len);
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
};


void process(){

    hashmap res = hashmap();
    size_t chunk_size = 1e5;

    char chunk[chunk_size + 30];
    int count = 0;
    int chunk_len = 0;

    for(read_chunk(chunk, chunk_size, chunk_len); chunk[0] != '\0'; read_chunk(chunk, chunk_size, chunk_len)){
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
          res.hash_insert(city, city_len, fval);
          line_length = 0;
        }
        else{
          line[line_length] = chunk[i];
          line_length++;
        }
      }
      count++;
      // if(count == 700){
      //   break;
      // }
    }

    // for(auto i : res){
    //   cout<<i.first.city<<" "<<i.second[0]<<" "<<i.second[1]<<" "<<i.second[2]<<" "<<i.second[3]<<endl;
    // }

    long long int total_count = 0;
    for(int i = 0; i < (10000); i++){
      if(res.hashtable[i] != -1){
        cout<<res.ht2[i].city<<" "<<res.ht2[i].min_val<<" "<<res.ht2[i].max_val<<" "<<res.ht2[i].total_sum<<" "<<res.ht2[i].count<<endl;
        total_count += res.ht2[i].count;
      }
    }

    cout<<total_count<<endl;
}

int main(){
    file = ifstream("measurements.txt", ios::in);

    if(file.is_open())
      process();
    else
      cout<<"not opening.\n";

    return 0;
}