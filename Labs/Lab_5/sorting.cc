#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <iomanip>

using namespace std;

/// Basic implementation for bubble sort with two nested loops.
/// The outer loop defines the range that is not yet sorted and the inner loop
/// passes over the unsorted range and swaps every unordered pair
/// You do not have to use the optimization heuristics that we described in class
/// but you can implement them if you would like.
template <typename T>
void bubbleSort(vector<T>& a) {
	for (int i = 0; i < a.size(); ++i)
	{
		for (int j = 0; j < a.size() - i - 1; ++j)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
			}
		}
	}
}

/// In insertion sort, we start with an array of one element and then we keep
/// expanding this array element-by-element while ensuring the array is sorted
/// after adding each element
template <typename T>
void insertionSort(vector<T>& a) {
    for (int i = 1; i < a.size(); ++i)
    {
        for (int j = i; j > 0 && a[j] < a[j - 1]; --j)
        {
            swap(a[j], a[j - 1]);
        }
    }
}

/// Selection sort makes n-1 passes over the array where in iteration i it selects
/// the i-th smallest element and places it in its correct position in the array.
template <typename T>
void selectionSort(vector<T>& a) {
	for (int i = 0; i < a.size() - 1; ++i)
	{
		for (int j = i + 1; j < a.size(); ++j)
		{
			if (a[i] > a[j])
			{
				swap(a[i], a[j]);
			}
		}
	}
}

/// Implement the original Shell sort algorithm which uses gaps of sizes
/// n/2, n/4, ..., 1
template <typename T>
void shellSort1(vector<T>& a) {
	for (int gap = a.size() / 2; gap > 0; gap = gap / 2)
	{
		for (int i = gap; i < a.size(); ++i)
		{
			int temp = a.at(i);
			
			int j;
			
			for (j = i; j >= gap && a.at(j - gap) > temp; j = j - gap)
			{
				a.at(j) = a.at(j - 1); 
			}
			
			a.at(j) = temp;
		}
	}
}

/// Use Hibbard's increments for the gaps which are in the form of 2^k-1
/// Find more details on page 298 of the book
template <typename T>
void shellSort2(vector<T>& a) {
	// TODO (Optional 10% bonus)
	for (int k = log(a.size() + 1); k > 0; --k)
	{
		int gap = pow(2, k) - 1;
		
		for (int i = gap; i < a.size(); ++i)
		{
			int temp = a.at(i);
			
			int j;
			
			for (j = i; j >= gap && a.at(j - gap) > temp; j = j - gap)
			{
				a.at(j) = a.at(j - 1);
			}
			
			a.at(j) = temp;
		}
	}
}

/// Check whether an array is sorted or not
template <typename T>
bool isSorted(vector<T> a) {
	for (int i = 0; i < a.size() - 1; i++) {
		if (a[i] > a[i+1]) {
			cout << "Elements a[" << i << "]= "<< a[i] << " and a["<<(i+1)<<"] = " << a[i+1] << " are out of order" << endl;
		  return false;
		}
	}
	return true;
}

int main() {
	// Simple test for sorting algorithms
	vector<int> values = {10, 3, 5, 7, 2, 1, 15, 13};
	vector<int> temp = values;
	bubbleSort(temp);
	EXPECT_TRUE(isSorted(temp));
	
	temp = values;
	insertionSort(temp);
	EXPECT_TRUE(isSorted(temp));

	temp = values;
	selectionSort(temp);
	EXPECT_TRUE(isSorted(temp));

	temp = values;
	shellSort1(temp);
	EXPECT_TRUE(isSorted(temp));
	
	temp = values;
	shellSort2(temp);
	EXPECT_TRUE(isSorted(temp));
	
	// Measure the running time as the input size increases
	cout << right << setw(16)  << "Size"
	     << setw(16)  << "Bubble"
	     << setw(16)  << "Insertion"
	     << setw(16)  << "Selection"
	     << setw(16)  << "Shell 1"
	     << setw(16)  << "Shell 2" << endl;

	for (int n = 1; n <= (1<<16); n *= 2) {
		cout << setw(16) << right << n;
		values.clear();
		for (int i = 0; i < n; i++)
			values.push_back(random());
		temp = values;
		clock_t begin = clock(); // Start the stopwatch
		bubbleSort(temp);
		clock_t end = clock(); // Stop the stopwatch
    double elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
    cout << setw(16) << elapsed_time;

		temp = values;
		begin = clock();
		insertionSort(temp);
		end = clock();
		elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
    cout << setw(16) << elapsed_time;

		temp = values;
		begin = clock();
		selectionSort(temp);
		end = clock();
		elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
    cout << setw(16) << elapsed_time;

		temp = values;
		begin = clock();
		shellSort1(temp);
		end = clock();
		elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
    cout << setw(16) << elapsed_time;

		temp = values;
		begin = clock();
		shellSort2(temp);
		end = clock();
		elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
    cout << setw(16) << elapsed_time;
    
    cout << endl;
	}
	
	return 0;
}
