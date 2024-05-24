#include<iostream>
#include<fstream>
// #include<thread>
#include<map>
#include<unordered_map>
#include<vector>
#include<string.h>
// #include<chrono>
// #include <iomanip>

using namespace std;

ifstream file;
// long long int total_count = 0;

void read_chunk(char *chunk, size_t chunk_size, int &chunk_len){
    // cout<<file.tellg()<<" ";
    // char* chunk = new char[chunk_size + 25];
    // chunk = "";
    // strcpy(chunk, "");
    // char temp[chunk_size + 1];
    // chunk[0] = '\0';
    memset(chunk, '\0', chunk_size);
    file.read(chunk, chunk_size);
    // chunk[chunk_size] = '\0';
    // chunk = temp;
    // memcpy(chunk, temp, chunk_size + 1);
    char buffer = chunk[chunk_size - 1];
    while(buffer != '\n' && file.read(&buffer, 1)){
        chunk[chunk_size] = buffer;
        chunk_size++;
    }
    chunk[chunk_size] = '\0';
    chunk_len = chunk_size;
    // cout<<file.tellg()<<" "<<chunk_size<<endl;
    // total_count += chunk_size;
    // return chunk;
}

// void min_val(map<string, vector<int>> & res, string & city, int value){
//   if(res[city][0] > value) res[city][0] = value;
// }

// void max_val(map<string, vector<int>> & res, string & city, int value){
//   if(res[city][1] < value) res[city][1] = value;
// }

// void avg_val(map<string, vector<int>> & res, string & city, int value){
//   res[city][2] += value;
//   res[city][3]++;
// }



struct char_struct{
  char city[50] = "\0";
  int len = 0;
  
  char_struct(){}
  char_struct(char* c, int l){
    memcpy(this->city, c, l + 1);
    this->len = l;
  }

  bool operator==(const char_struct& a) const
  {
    if(a.len != this->len){
      return 0;
    }
    const int rc = memcmp(this->city, a.city, len);
    if(rc == 0)
      return 1;
    
    return 0;
  }
  struct custom_hash {
    size_t operator()(const char_struct & key) const {
      // int len = key.length();
      return (((key.city[0] - 'A') << 24) + ((key.city[1] - 'A') << 16) + ((key.city[key.len - 2] - 'A') << 8) + ((key.city[key.len - 1] - 'A')));

    }
  };
  
};

void insert(unordered_map< char_struct, vector<float>, char_struct::custom_hash> & res, char *city, int len, float value){
  // total_count++;
  vector<float>* tmp = &res[char_struct(city, len)];
  if((*tmp).size() == 0){
    (*tmp) = {value, value, value, 1};
  }
  else{
    // vector<float>* tmp = &res[city];
    if((*tmp)[0] > value) (*tmp)[0] = value;
    if((*tmp)[1] < value) (*tmp)[1] = value;
    (*tmp)[2] += value;
    (*tmp)[3]++;

    // res[city] = tmp;
    tmp = NULL;
  }
  // else{
  //   min_val(res, city, value);
  //   max_val(res, city, value);
  //   avg_val(res, city, value);
  // }

}

void process(){
    unordered_map< char_struct, vector<float>, char_struct::custom_hash> res;
    size_t chunk_size = 1e6;
    // for(int i = 0 ; i < 1e1; i++){
    //   string chunk;
    //   chunk.reserve(chunk_size + 25);
    //   read_chunk(chunk, chunk_size);
    //   cout<<chunk;
    // }

    // using std::chrono::high_resolution_clock;
    // using std::chrono::duration_cast;
    // using std::chrono::duration;
    // using std::chrono::milliseconds;

    // auto t1 = chrono::high_resolution_clock::now();
    

    char chunk[chunk_size + 30];
    // chunk.reserve(chunk_size + 30);
    // read_chunk(chunk, chunk_size);

    int count = 0;
    int chunk_len = 0;

    for(read_chunk(chunk, chunk_size, chunk_len); chunk[0] != '\0'; read_chunk(chunk, chunk_size, chunk_len)){
      // cout<<chunk<<endl;
      char line[50];
      int line_length = 0;
      char city[50];
      int city_len;
      float fval;
      int ival;
      // int chunk_len = chunk.length();

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
          // total_count++;
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
          // fval = atof(line) * 100;
          // ival = (int) fval;
          // cout<<fval<<endl;
          // cout<<line<<" ";
          // cout<<ival<<'\n';
          insert(res, city, city_len, fval);
          line_length = 0;
        }
        else{
          line[line_length] = chunk[i];
          line_length++;
        }
      }
      // break;
      // cout<<count<<'\n';
      count++;
      if(count == 500){
        break;
      }
      // insert(res, city, ival);
    }

    // auto t2 = chrono::high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    // auto ms_int = chrono::duration_cast<chrono::milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    // chrono::duration<double, std::milli> ms_double = t2 - t1;

    // std::cout << ms_int.count() << "ms\n";
    // std::cout << ms_double.count() << "ms\n";


    // double total_rows = 0;
    for(auto i : res){
      cout<<i.first.city<<" "<<i.second[0]<<" "<<i.second[1]<<" "<<i.second[2]<<" "<<i.second[3]<<endl;
      // total_rows += i.second[3];
    }
    // cout<<setprecision(10)<<total_rows<<endl;
    // cout<<total_count<<endl;

    // cout<<chunk<<endl;

    // if(chunk == ""){
    //   cout<<"working"<<endl;
    // }

    // while(chunk != ""){
        
    //     chunk = read_chunk(1e7);
    // }
}

int main(){
    file = ifstream("measurements.txt", ios::in);

    if(file.is_open())
      process();
    else
      cout<<"not opening.\n";

    return 0;
}