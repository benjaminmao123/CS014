#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

void generate_random_numbers(vector<int>& values) {
    for (auto& x : values) {
      x = rand();
    }
}

void insertionsort(vector<int>& values) {
    // TODO: Convert the pseudo code shown in class to C++
    for (int i = 1; i < values.size(); ++i)
    {
        for (int j = i; j > 0 && values[j] < values[j - 1]; --j)
        {
            swap(values[j], values[j - 1]);
        }
    }
}

int main() {
    srand(0);
    vector<int> sizes = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
    for (auto size : sizes) {
      vector<int> values(size);
      clock_t begin = clock(); // Start the stopwatch
      generate_random_numbers(values);
      clock_t end = clock(); // Stop the stopwatch
      double elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
      std::cout << "Size " << size << ": Total time " << elapsed_time << " secs" << std::endl;
    }
}

