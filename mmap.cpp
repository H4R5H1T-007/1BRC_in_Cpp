#include <iostream>
#include <thread>
#include <vector>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

struct ThreadData {
  char* data;
  size_t size;
};

void read_file(ThreadData* data) {
  for (size_t i = 0; i < data->size; i++) {
    cout << data->data[i];
  }
}

int main() {
  // Open the file
  int fd = open("measurements.txt", O_RDONLY);
  if (fd == -1) {
    cerr << "Error opening file" << endl;
    return 1;
  }

  // Get the file size
//   size_t size = lseek(fd, 0, SEEK_END);
    size_t size = 1e7;

  // Create a memory map of the file
  char* data = (char*)mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
  if (data == MAP_FAILED) {
    cerr << "Error creating memory map" << endl;
    return 1;
  }

  // Create a vector of thread data
  vector<ThreadData> thread_data;
  for (size_t i = 0; i < 4; i++) {
    thread_data.push_back({data + i * size / 4, size / 4});
  }

  // Create a vector of threads
  vector<thread> threads;
  for (size_t i = 0; i < thread_data.size(); i++) {
    threads.push_back(thread(read_file, &thread_data[i]));
  }

  // Wait for all threads to finish
  for (thread& thread : threads) {
    thread.join();
  }

  // Unmap the file
  munmap(data, size);

  // Close the file
  close(fd);

  return 0;
}