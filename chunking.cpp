#include<iostream>
#include<fstream>
// #include<thread>
#include<map>
#include<unordered_map>
#include<vector>
#include<string.h>
// #include<chrono>
#include<iomanip>

using namespace std;

ifstream file;
long long int length;

void read_chunk(string &chunk, size_t chunk_size = 6e4){
    // char* chunk = new char[chunk_size + 25];
    // chunk = "";
    // strcpy(chunk, "");
    char temp[chunk_size + 1];
    memset(temp, '\0', chunk_size + 1);
    file.read(temp, chunk_size);
    chunk = temp;
    char buffer = chunk[chunk_size - 1];
    while(buffer != '\n' && file.read(&buffer, 1)){
        chunk.push_back(buffer);
        chunk_size++;
    }
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

void insert(unordered_map< string, vector<float> > & res, string & city, float value){
  vector<float>* tmp = &res[city];
  // opertaor[] -> pointer -> modify
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
    unordered_map< string, vector<float> > res;
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
    

    string chunk;
    chunk.reserve(chunk_size + 30);
    // read_chunk(chunk, chunk_size);

    int count = 0;

    for(read_chunk(chunk, chunk_size); chunk.length() != 0; read_chunk(chunk, chunk_size)){
      // cout<<chunk<<endl;
      char line[50];
      int line_length = 0;
      string city;
      float fval;
      int ival;
      int chunk_len = chunk.length();

      // fetching city name and value from each line
      // for(auto c : chunk)
      // i < chunk.size() -> 1e9 -> chunk_len
      for(int i = 0; i < chunk_len; i++){
        if(chunk[i] == ';'){
          line[line_length] = '\0';
          city = line;
          line_length = 0;
          // cout<<city<<" ";
        }
        else if(chunk[i] == '\n'){
          line[line_length] = '\0';

          // basically custom atoi for this code
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
          insert(res, city, fval);
          line_length = 0;
        }
        else{
          line[line_length] = chunk[i];
          line_length++;
        }
      }
      // break;
      // cout<<count<<'\n';
      // count++;
      // if(count == 500){
      //   break;
      // }
      // insert(res, city, ival);
    }

    // auto t2 = chrono::high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    // auto ms_int = chrono::duration_cast<chrono::milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    // chrono::duration<double, std::milli> ms_double = t2 - t1;

    // std::cout << ms_int.count() << "ms\n";
    // std::cout << ms_double.count() << "ms\n";

    double total_count = 0;
    for(auto i : res){
      cout<<i.first<<" "<<i.second[0]<<" "<<i.second[1]<<" "<<i.second[2]<<" "<<i.second[3]<<endl;
      total_count += i.second[3];
    }
    cout<<setprecision(10)<<total_count<<endl;

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