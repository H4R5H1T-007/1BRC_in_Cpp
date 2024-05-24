#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

void read_chunk(ifstream &file){
  char buffer;
  long long int count = 0;
  while(file.read(&buffer, 1)){
    if(buffer == '\n'){
      count++;
    }
  }
  cout<<count<<endl;
}

int main(){
  ifstream file("measurements.txt");
  read_chunk(file);
  return 0;
}