#include<thread>
#include<cstdlib>
#include<iostream>
#include <fstream>
#include<vector>
#include<string>
#include<mutex>
#include<map>

using namespace std;

mutex mtx;
int count = 0;

void min_val(map<string, vector<int>> & res, string & city, int value){
  if(res[city][0] > value) res[city][0] = value;
}

void max_val(map<string, vector<int>> & res, string & city, int value){
  if(res[city][1] < value) res[city][1] = value;
}

void avg_val(map<string, vector<int>> & res, string & city, int value){
  res[city][2] += value;
  res[city][3]++;
}

void insert(map<string, vector<int>> & res, string & city, int value){
  if(res.count(city) == 0){
    res[city] = {value, value, value, 1};
  }
  else{
    min_val(res, city, value);
    max_val(res, city, value);
    avg_val(res, city, value);
  }
}

bool read_line(ifstream &file, string & line){
    bool res = 0;
    mtx.lock();
    if(!file.eof()){
        getline(file, line);
        res = 1;
        count++;
    }
    mtx.unlock();
    return res;
}

map<string, vector<int>> file_read(int id, ifstream & file){
    
    string line;
    map<string, vector<int>> res;

  if(file.is_open()){
        
    while(read_line(file, line)){
        string key;
        float value;
        int semiColonIndex = 0;
        for(semiColonIndex = 0; semiColonIndex < line.length() && line[semiColonIndex] != ';'; semiColonIndex++){
        key.push_back(line[semiColonIndex]);
        }
        string temp;
        semiColonIndex++;
        while(semiColonIndex < line.length()){
        if(line[semiColonIndex] == '.'){
        }
        else
            temp.push_back(line[semiColonIndex]); 
        
        semiColonIndex++;
        }
        value = stoi(temp);
        insert(res, key, value);
        if(count%(10000000) == 0){
            cout<<"thread id "<<id<<" has reached to count "<<count<<endl;
        }
    }

  }
    return res;
}

int main(){
    // int a = 0, b = 0;
    // std::thread t1(temp, std::ref(a));
    // std::thread t2(temp, std::ref(b));

    // t1.join(); t2.join();
    // std::cout<<a<<" "<<b<<std::endl;

    // thread t1(file_read);
    // thread t2(file_read);

    // t1.join(); t2.join();
    
    ifstream file("measurements.txt", ios::in);

    int thread_count = 6;
    thread t[thread_count];
    for(int i = 0; i < thread_count; i++){
        t[i] = thread(file_read, i, ref(file));
    }

    for(int i = 0; i < thread_count; i++){
        t[i].join();
    }

    // file_read(1, file);

    return 0;
}