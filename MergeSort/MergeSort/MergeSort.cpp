// C++ program for Merge Sort
#include <iostream>
#include <ctime>
#include <chrono>
#include <Windows.h>

using namespace std;

int steps = 0;
// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(int array[], int const left, int const mid,
	int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	// Create temp arrays
	auto* leftArray = new int[subArrayOne],
		* rightArray = new int[subArrayTwo];

	// Copy data to temp arrays leftArray[] and rightArray[]
	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne
		= 0, // Initial index of first sub-array
		indexOfSubArrayTwo
		= 0; // Initial index of second sub-array
	int indexOfMergedArray
		= left; // Initial index of merged array

	// Merge the temp arrays back into array[left..right]
	while (indexOfSubArrayOne < subArrayOne
		&& indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne]
			<= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray]
				= leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
			
		}
		else {
			array[indexOfMergedArray]
				= rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
			
		}
		indexOfMergedArray++;
		steps++;
		
	}
	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray]
			= leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
		steps++;
	}
	// Copy the remaining elements of
	// right[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray]
			= rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
		steps++;
	}
	delete[] leftArray;
	delete[] rightArray;
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end)
		return; // Returns recursively

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

// UTILITY FUNCTIONS
// Function to print an array
void printArray(int A[], int size)
{
	for (auto i = 0; i < size; i++)
		cout << A[i] << " ";
}

// Driver code
int main()
{
	//int arr[] = { 12, 11, 13, 5, 6, 7,15,3,9,21,15, 1, 90,56,34};
	//int arr[] = { 12, 11, 13, 5, 6, 7,15,3,9,21,15, 1, 90,56,34, 23, 54, 22, 19,17,18,72,51,49,52,24,39,30,31 ,10};
	//int arr[] = { 12, 11, 13, 5, 6, 7,15,3,9,21,15, 1, 90,56,34, 23, 54, 22, 19,17,18,72,51,49,52,24,39,30,31 ,10,91,80,78,77,75 };
	//int arr[] = { 12, 11, 13, 5, 6, 7,15,3,9,21,15, 1, 90,56,34, 23, 54, 22, 19,17,18,72,51,49,52,24,39,30,31 ,10,91,80,78,77,75,61,62,66,68,44 };
	int arr[] = { 12, 11, 13, 5, 6, 7,15,3,9,21,15, 1, 90,56,34, 23, 54, 22, 19,17,18,72,51,49,52,24,39,30,31 ,10,91,80,78,77,75,61,62,66,68,44,43,41 ,71,70,25};

	//int arr[] = { 12, 11, 13, 5, 6, 7,15,3,9,21,15, 1, 90,56,34, 23, 54, 22, 19,17,18,72,51,49,52,24,39,30,31 ,10,91,80,78,77,75,61,62,66,68,44,43,41 ,71,70,25,26,27 };
	auto arr_size = sizeof(arr) / sizeof(arr[0]);

	cout << "Given array is \n";
	printArray(arr, arr_size);
	cout << endl << "Size " << arr_size << endl;
	

	auto start = chrono::steady_clock::now();

	// do some stuff here

	mergeSort(arr, 0, arr_size - 1);

	auto end = chrono::steady_clock::now();
	cout << "Merge Sort" << endl;
	cout << "Elapsed time in nanoseconds: "
		<< chrono::duration_cast<chrono::nanoseconds>(end - start).count()
		<< " ns" << endl;

	cout << "Elapsed time in microseconds: "
		<< chrono::duration_cast<chrono::microseconds>(end - start).count()
		<< " µs" << endl;

	cout << "Elapsed time in milliseconds: "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " ms" << endl;

	cout << steps;


	cout << "\nSorted array is \n";
	printArray(arr, arr_size);
	return 0;
}

// This code is contributed by Mayank Tyagi
// This code was revised by Joshua Estes
