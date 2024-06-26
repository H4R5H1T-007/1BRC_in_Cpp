#include<thread>
#include<vector>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<string.h>
#include<fstream>
#include<iostream>


using namespace std;



struct hashnode{
  char city[50] = "\0";
  int len = 0;
  int min_val = 999, max_val = -999;
  long long int total_sum = 0;
  int count = 0;

  hashnode(){}
  hashnode(const char * c, int l){
    memcpy(this->city, c, l + 1);
    this->city[l] = '\0';
    this->len = l;
  }
  void node_insert(int value){
    // if(this->count == 0){
    //   this->count = 1;
    //   this->min_val = this->max_val = this->total_sum = value;
    // }
    // else{
    this->count++;
    this->min_val = ((this->min_val > value) ? value : this->min_val);
    this->max_val = ((this->max_val < value) ? value : this->max_val);
    this->total_sum += value;
    // }
  }
  void final_insert(int minval, int maxval, long long int totalval, int countval){
    // if(count == 0){
    //   min_val = minval;
    //   max_val = maxval;
    // }
    // else{
    min_val = ((min_val > minval) ? minval : min_val);
    max_val = ((max_val < maxval) ? maxval : max_val);
    // }
    total_sum += totalval;
    count += countval;
  }
};

struct hashmap{
  int max_size = 8192;
  int hashtable[8192];
  hashnode ht2[8192];
  
  hashmap(){
    memset(this->hashtable, -1, this->max_size*sizeof(int));
  }

  unsigned int hash (const char *str, unsigned int len)
  {
    static unsigned short asso_values[] =
      {
        1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
        1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
        1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
        1269, 1269,  110, 1269, 1269, 1269, 1269, 1269, 1269,    0,
        1269,    0, 1269, 1269, 1269,    0,    0, 1269, 1269, 1269,
        1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
        1269, 1269, 1269, 1269, 1269,  145,   10,  240,   65,  175,
          33,  413,  320,  280,   30,  190,  325,    0,  340,  335,
        170, 1269,  385,  105,  115,   40,  456,  190,    0,  340,
          0, 1269, 1269, 1269, 1269, 1269, 1269,    0,  280,  280,
        310,   15,   15,  250,  225,    5,  210,   35,   25,   90,
          0,   30,  325,    5,    5,   20,  105,  200,  275,  315,
          5,  260,  130, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
        1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
        1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
        1269, 1269, 1269,    0, 1269, 1269, 1269, 1269, 1269, 1269,
        1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,    5,  325,
        1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
        1269, 1269, 1269, 1269,   20, 1269, 1269, 1269,   10, 1269,
        1269, 1269, 1269, 1269, 1269,    5,   10,    0, 1269, 1269,
        1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
        1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
        1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
        1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
        1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
        1269, 1269, 1269, 1269, 1269, 1269
      };
    unsigned int hval = len;

    switch (hval)
      {
        default:
          hval += asso_values[(unsigned char)str[4]];
        /*FALLTHROUGH*/
        case 4:
        case 3:
          hval += asso_values[(unsigned char)str[2]];
        /*FALLTHROUGH*/
        case 2:
        case 1:
          hval += asso_values[(unsigned char)str[0]];
          break;
      }
    return hval + asso_values[(unsigned char)str[len - 1]];
  }

  void hash_insert(const char * city, int len, int value){
    // hashfunction to create int out of string
    // int index = fnv1a_hashfunc(city, len);
    // unsigned int hash = fnv1a_hashfunc(city, len);
    // size_t index = (size_t)(hash & (unsigned int)(max_size - 1));
    unsigned int index = hash(city, len);
    // unsigned int index = hash_index;
    // int index = hashfunc(city, len);
    // cout<<index<<endl;
    // linear probing
    // checking from hashtable if it contains value then checking if it's the same city as given in arg
    // while(hashtable[index] != -1 && (len != ht2[index].len || (memcmp(ht2[index].city, city, len) != 0))){
    //   index++;
    //   index %= this->max_size;
    // }
    if(hashtable[index] == -1){
      ht2[index] = hashnode(city, len);
      hashtable[index] = 1;
    }
    ht2[index].node_insert(value);
  }

  void final_hash_insert(char * city, int len, int minval, int maxval, long long int totalval, int countval){
    // int index = fnv1a_hashfunc(city, len);
    // unsigned int hash = fnv1a_hashfunc(city, len);
    // size_t index = (size_t)(hash & (unsigned int)(max_size - 1));
    // unsigned int index = hash(city, len);
    unsigned int index = 0;
    int temp = 0;
    while(temp != len){
      index = (index * 31) + (unsigned char)city[temp];
      temp++;
    }
    // index %= max_size;
    index = (index & (max_size - 1));
    // int index = hashfunc(city, len);
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

  unsigned int hashfunc(const char * city, int len){
    // return ((city[0]<<14) | (city[len - 1]<<6) | len) % this->max_size;
    return (city[0]^city[len-1]^len)%max_size;
  }

  // 13 bit fnv1a hash function
  // http://www.isthe.com/chongo/tech/comp/fnv/
  unsigned int fnv1a_hashfunc(const char * city, int len){
    unsigned const int fnv_prime = 16777619;
    // unsigned const int mask = ((1<<13) - 1);
    unsigned int hash = 2166136261;
    for(int i = 0; i < len; i++){
      hash ^= city[i];
      hash *= fnv_prime;
    }

    // hash = ((hash >> 13) ^ (hash & mask)) % max_size;
    // hash = 

    return hash;
  }

};

int custom_atof(const char * line, int line_length){
    int fval = 1;
    int tmp = 1;
    // if(line[0] == '-'){
    //   fval = -1;
    // }
    // for(int j = line_length - 1; j >= 0 && line[j] != '.'; j--){
    //     tmp /= 10;
    //     }
    // for(int j = line_length - 1; j >= 0; j--){
    //     if(line[j] == '.'){
    //         continue;
    //     }
    //     else if(line[j] == '-'){
    //         fval *= -1;
    //     }
    //     else{
    //         fval += (tmp * (line[j] - '0'));
    //         tmp *= 10;
    //     }
    // }

    for(int j = 0; j < line_length; j++){
      // int org_idx = line_length - j - 1;
      int digit = (int)line[line_length - j - 1];
      switch (digit)
      {
      case '.':
        /* code */
        break;
      case '-':
        fval *= -1;
        break;
      default:
        fval += (tmp * (digit - '0'));
        tmp *= 10;
        break;
      }
    }
   
    return fval;
}

void city_parser(char * city, char * line, int & line_length, int & city_len){
    line[line_length] = '\0';
    memcpy(city, line, line_length + 1);
    city_len = line_length;
    line_length = 0;
    // cout<<city<<" "<<line<<endl;
}

void line_parser(hashmap & res, const char * chunk, int city_len, int val_length){
  int ival = custom_atof(chunk - val_length, val_length);
  res.hash_insert(chunk - val_length - city_len - 1, city_len, ival);
}

static void process(hashmap &res, const char * chunk, int chunk_len){
    char line[50];
    int line_length = 0;
    char city[50];
    int city_len;
    // float fval;
    int ival;
    // cout<<chunk<<endl;
    // int count = 0;
    const char * start = chunk;
    const char * end = chunk + chunk_len;
    while(start != end && *(end-1) != '\n'){
      end--;
    }
    
    while(start != end){
      unsigned int len = 0;
      unsigned int h = 0;
      const char * linestart = start;
      while (start[len] != ';') {
        h = (h * 31) + (unsigned char)start[len];
        len += 1;
      }
      // h %= res.max_size;
      h = (h & (res.max_size - 1));
      while(res.hashtable[h] != -1 && (len != res.ht2[h].len || (memcmp(res.ht2[h].city, start, len) != 0))){
        h++;
        h %= res.max_size;
      }
      start += len + 1;

      int mod = 1;
      if (*start == '-') {
        mod = -1;
        start++;
      }

      if (start[1] == '.') {
        ival = ((start[0] * 10) + start[2] - ('0' * 11)) * mod;
        start += 4;
      }
      else{
        ival = (start[0] * 100 + start[1] * 10 + start[3] - ('0' * 111)) * mod;
        start += 5;
      }

      if(res.hashtable[h] == -1){
        res.hashtable[h] = 1;
        res.ht2[h] = hashnode(linestart, len);
      }
      res.ht2[h].node_insert(ival);
    }
    // cout<<"Done"<<endl;
    // // fetching city name and value from each line
    // for(int i = 0; i < chunk_len; i++){
    //   switch (chunk[i]){
    //   case ';':
    //     /* code */
    //     // city_parser(city, line, line_length, city_len);
    //     city_len = line_length;
    //     line_length = 0;
    //     break;
    //   case '\n':
    //     // line[line_length] = '\0';
    //     // cout<<line<<endl;
    //     // ival = custom_atof(line, line_length);
    //     // res.hash_insert(city, city_len, ival);
    //     line_parser(res, chunk + i, city_len, line_length);
    //     line_length = 0;
    //     break;
    //   case '\0':
    //     return ;
    //   default:
    //     // line[line_length] = chunk[i];
    //     line_length++;
    //     break;
    //   }
    // }
    //   if(chunk[i] == ';'){
    //       // line[line_length] = '\0';
    //       // memcpy(city, line, line_length + 1);
    //       // city_len = line_length;
    //       // line_length = 0;
    //       // cout<<city<<" ";
    //       city_parser(city, line, line_length, city_len);
    //   }
    //   else if(chunk[i] == '\n'){
    //       line[line_length] = '\0';

    //       // basically custom atof for this code
    //       // fval = 0;
    //       // float tmp = 1;
    //       // for(int j = line_length - 1; j >= 0 && line[j] != '.'; j--){
    //       // tmp /= 10;
    //       // }
    //       // for(int j = line_length - 1; j >= 0; j--){
    //       // if(line[j] == '.'){
    //       //     continue;
    //       // }
    //       // else if(line[j] == '-'){
    //       //     fval *= -1;
    //       // }
    //       // else{
    //       //     fval += (tmp * (line[j] - '0'));
    //       //     tmp *= 10;
    //       // }

    //       // }
    //       ival = custom_atof(line, line_length);
    //       // cout<<fval<<endl;
    //       // insert(res, city, city_len, fval);
    //       res.hash_insert(city, city_len, ival);
    //       line_length = 0;
    //   }
    //   else{
    //       line[line_length] = chunk[i];
    //       line_length++;
    //   }
    // }

    // free(chunk);
    // count++;
    // if(count == 700){
    // break;
    // }
}

// used https://stackoverflow.com/questions/15752659/thread-pooling-in-c11 and modified a bit for our usecase
struct threadpool{
    vector<thread> threads;
    queue< pair <char*, int> > jobs_queue;
    int qsize = 100;
    int max_threads;
    mutex queue_mutex;
    condition_variable mutex_condition;
    // condition_variable queue_full;
    bool should_terminate = 0;

    threadpool(int max_t, hashmap * res){
        max_threads = max_t;
        threads.resize(max_threads);
        for(int i = 0; i < max_threads; i++){
            // threads.emplace_back(thread(threadloop, this));
            threads[i] = thread(&threadpool::threadloop, this, ref(res[i]));
        }
        // should_terminate = 0;
    }

    void threadloop(hashmap & res){
        // hashmap res = hashmap();
        while (true) {
            // std::function<void()> job;
            // cout<<"job"<<endl;
            pair<char *, int> param;
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                // queue_full.wait(lock, [this] {
                //   return jobs_queue.empty();
                // });
                // queue_full.notify_all();
                mutex_condition.wait(lock, [this] {
                    return !jobs_queue.empty() || should_terminate;
                });
                if (should_terminate) {
                    return;
                }
                param = jobs_queue.front();
                jobs_queue.pop();
                // cout<<param.first<<endl;
                qsize++;
            }
            process(res, param.first, param.second);
            delete[] param.first;
        }
    }

    void queue_push(char * chunk, int len){
        // char temp[len];
        // memcpy(temp, chunk, len);
        // string temp(chunk);
        {
            unique_lock<mutex> lock(queue_mutex);
            // queue_full.wait(lock, [this] {
            //     return jobs_queue.size() >= max_qsize;
            // });
            jobs_queue.push({chunk, len});
            qsize--;
        }
        mutex_condition.notify_one();
    }

    bool queue_full(){
      bool queue_full;
      {
        unique_lock<mutex> lock(queue_mutex);
        queue_full = (qsize == 0);
        // cout<<qsize<<" "<<jobs_queue.size()<<endl;
      }
      return queue_full;
    }

    bool stop_busy(){
      bool poolbusy;
      {
        unique_lock<mutex> lock(queue_mutex);
        poolbusy = !jobs_queue.empty();
      }
      return poolbusy;
    }

    void stop(){
        {
            unique_lock<mutex> lock(queue_mutex);
            should_terminate = true;
        }
        mutex_condition.notify_all();
        for(int i = 0; i < max_threads; i++){
            threads[i].join();
        }
        threads.clear();
    }
};

void read_chunk(ifstream & file, char *chunk, size_t chunk_size, int &chunk_len){
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

int main(){
    ifstream file = ifstream("/Users/harshitgupta/Developer/Timepass/DockerFiles/measurements.txt", ios::binary);
    int chunk_size = 64e6;
    int chunk_len = 0;
    int max_thread = 7;
    // cout<<"test"<<endl;
    hashmap res[max_thread];
    // cout<<"test"<<endl;
    for(int i = 0; i < max_thread; i++){
      res[i] = hashmap();
    }
    threadpool tp = threadpool(max_thread, res);
    int count = 0;
    // for(read_chunk(file, chunk, chunk_size, chunk_len); chunk[0] != '\0'; read_chunk(file, chunk, chunk_size, chunk_len)){
    //   while(tp.queue_full());
    //   tp.queue_push(chunk, chunk_len);
    //   count++;
    //   // if(count == 1){
    //   //   break;
    //   // }
    // }
    

    char * chunk = new char[1];
    chunk[0] = '0';
    // read_chunk(file, chunk, chunk_size, chunklen);
    while(chunk[0] != '\0'){
      // cout<<chunk[0]<<endl;
      chunk = new char[chunk_size + 50];
      read_chunk(file, chunk, chunk_size, chunk_len);
      // while(tp.queue_full());
      tp.queue_push(chunk, chunk_len);
      // count++;
      // if(count == 1){
      //   break;
      // }
    }

    while(tp.stop_busy());
    tp.stop();
    // cout<<"Thread work completed\n";

    // hashmap final_res = hashmap();
    // vector<char*> final_cities;
    // vector<int> final_cities_len;
    // vector<vector<float>> final_results;
    // int num_cities = final_cities.size();
    // for(int i = 0; i < res[0].max_size; i++){
    //   if(res[0].hashtable[i] != -1){
    //     final_cities.emplace_back(res[0].ht2[i].city);
    //     final_cities_len.emplace_back(res[0].ht2[i].len);
    //     final_results.push_back({res[0].ht2[i].min_val, res[0].ht2[i].max_val, res[0].ht2[i].total_sum, (float)res[0].ht2[i].count});
    //   }
    // }

    // for(int i = 1; i < max_thread; i++){
    //   for(int j = 0; j < num_cities; j++){
    //     vector<float> temp = res[i].lookup(final_cities[j], final_cities_len[j]);
    //     final_results[j][0] = min(final_results[j][0], temp[0]);
    //     final_results[j][1] = max(final_results[j][1], temp[1]);
    //     final_results[j][2] += temp[2];
    //     final_results[j][3] += count;
    //   }
    // }
    
    hashmap final_res = hashmap();

    long long int total_count = 0;
    // for(int i = 0 ; i < num_cities; i++){
    //   cout<<final_cities[i]<<" "<<final_results[i][0]<<" "<<final_results[i][1]<<" "<<final_results[i][2]<<" "<<final_results[i][3]<<endl;
    //   total_count += (int) final_results[i][3];
    // }
    for(int i = 0; i < max_thread; i++){
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
        // cout<<tmp.city<<"\n";
        cout<<tmp.city<<" "<<tmp.min_val<<" "<<tmp.max_val<<" "<<tmp.total_sum<<" "<<tmp.count<<endl;
        total_count += tmp.count;
      }
    }

    cout<<total_count<<endl;

    return 0;
}