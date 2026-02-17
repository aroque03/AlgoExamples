// =============================================================================
// Merge Sort - An Efficient Divide-and-Conquer Sorting Algorithm
// =============================================================================
//
// Overview:
//   Merge Sort divides the array into two halves, recursively sorts each half,
//   and then merges the two sorted halves back together. It is one of the most
//   efficient general-purpose sorting algorithms and guarantees O(n log n)
//   performance regardless of input order.
//
// How it works:
//   1. Divide: Split the array into two halves at the midpoint.
//   2. Conquer: Recursively sort each half.
//   3. Combine: Merge the two sorted halves into a single sorted array.
//
//   The merge step is the key operation. It uses temporary arrays to hold the
//   two halves, then compares elements from each half one by one, placing the
//   smaller element into the original array. Any remaining elements from either
//   half are copied over at the end.
//
// Time Complexity:
//   - Best Case:    O(n log n) - always divides and merges
//   - Average Case: O(n log n) - consistent across all inputs
//   - Worst Case:   O(n log n) - no degradation on any input pattern
//
// Space Complexity: O(n) - requires additional space for temporary arrays
//                   during the merge step.
//
// Stability: Stable - equal elements maintain their relative order because
//            the merge step uses <= (less than or equal) when comparing
//            elements from the left subarray.
//
// =============================================================================

#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

// Global step counter to track the number of merge operations performed.
// This is useful for analyzing the algorithm's performance on different inputs.
int steps = 0;

// -----------------------------------------------------------------------------
// merge - Merges two sorted subarrays into a single sorted subarray.
//
// Parameters:
//   array[] - the array containing both subarrays
//   left    - the starting index of the first subarray
//   mid     - the ending index of the first subarray (midpoint)
//   right   - the ending index of the second subarray
//
// The two subarrays being merged are:
//   array[left..mid]     - first (left) subarray
//   array[mid+1..right]  - second (right) subarray
//
// How the merge works:
//   1. Calculate the sizes of both subarrays.
//   2. Copy data into temporary arrays (leftArray and rightArray).
//   3. Use three index pointers to walk through both temp arrays and the
//      original array, always placing the smaller element next.
//   4. Copy any remaining elements from whichever temp array isn't exhausted.
//   5. Free the dynamically allocated temporary arrays.
// -----------------------------------------------------------------------------
void merge(int array[], int const left, int const mid,
	int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	// Create temp arrays to hold copies of the two halves.
	// We need copies because the merge overwrites the original array.
	auto* leftArray = new int[subArrayOne],
		* rightArray = new int[subArrayTwo];

	// Copy data from the original array into temp arrays
	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne
		= 0, // Index tracking position in left subarray
		indexOfSubArrayTwo
		= 0; // Index tracking position in right subarray
	int indexOfMergedArray
		= left; // Index tracking position in merged result

	// Merge the temp arrays back into array[left..right].
	// Compare elements from both subarrays and place the smaller one first.
	// Using <= ensures stability (equal elements from the left subarray
	// come first, preserving their original relative order).
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

	// Copy any remaining elements from the left subarray.
	// If the left subarray has elements left, they are already sorted
	// and all greater than what has been merged so far.
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray]
			= leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
		steps++;
	}

	// Copy any remaining elements from the right subarray.
	// Same logic as above for the right side.
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray]
			= rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
		steps++;
	}

	// Free dynamically allocated memory to prevent memory leaks
	delete[] leftArray;
	delete[] rightArray;
}

// -----------------------------------------------------------------------------
// mergeSort - Recursively divides and sorts an array using Merge Sort.
//
// Parameters:
//   array[] - the array to be sorted
//   begin   - the starting index of the subarray to sort (left boundary)
//   end     - the ending index of the subarray to sort (right boundary)
//
// The recursion works as follows:
//   - Base case: if begin >= end, the subarray has 0 or 1 elements and is
//     already sorted, so we return immediately.
//   - Recursive case: find the midpoint, sort the left half, sort the right
//     half, then merge the two sorted halves.
//
// The midpoint is calculated as begin + (end - begin) / 2 rather than
// (begin + end) / 2 to avoid potential integer overflow when begin and end
// are large values.
// -----------------------------------------------------------------------------
void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end)
		return; // Base case: subarray of size 0 or 1 is already sorted

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);       // Sort the left half
	mergeSort(array, mid + 1, end);     // Sort the right half
	merge(array, begin, mid, end);      // Merge the two sorted halves
}

// -----------------------------------------------------------------------------
// printArray - Utility function to print all elements of an array.
//
// Parameters:
//   A[]  - the array to print
//   size - the number of elements in the array
// -----------------------------------------------------------------------------
void printArray(int A[], int size)
{
	for (auto i = 0; i < size; i++)
		cout << A[i] << " ";
}

// -----------------------------------------------------------------------------
// Driver code - Demonstrates Merge Sort with performance measurement.
//
// The program:
//   1. Prints the unsorted array and its size.
//   2. Runs Merge Sort while measuring elapsed time.
//   3. Prints the sorted array, step count, and timing results.
//
// Multiple test arrays of varying sizes are provided below (commented out).
// Uncomment different arrays to test performance on different input sizes.
// -----------------------------------------------------------------------------
int main()
{
	//int arr[] = { 12, 11, 13, 5, 6, 7, 15, 3, 9, 21, 15, 1, 90, 56, 34 };
	//int arr[] = { 12, 11, 13, 5, 6, 7, 15, 3, 9, 21, 15, 1, 90, 56, 34, 23, 54, 22, 19, 17, 18, 72, 51, 49, 52, 24, 39, 30, 31, 10 };
	//int arr[] = { 12, 11, 13, 5, 6, 7, 15, 3, 9, 21, 15, 1, 90, 56, 34, 23, 54, 22, 19, 17, 18, 72, 51, 49, 52, 24, 39, 30, 31, 10, 91, 80, 78, 77, 75 };
	//int arr[] = { 12, 11, 13, 5, 6, 7, 15, 3, 9, 21, 15, 1, 90, 56, 34, 23, 54, 22, 19, 17, 18, 72, 51, 49, 52, 24, 39, 30, 31, 10, 91, 80, 78, 77, 75, 61, 62, 66, 68, 44 };
	int arr[] = { 12, 11, 13, 5, 6, 7, 15, 3, 9, 21, 15, 1, 90, 56, 34, 23, 54, 22, 19, 17, 18, 72, 51, 49, 52, 24, 39, 30, 31, 10, 91, 80, 78, 77, 75, 61, 62, 66, 68, 44, 43, 41, 71, 70, 25 };
	//int arr[] = { 12, 11, 13, 5, 6, 7, 15, 3, 9, 21, 15, 1, 90, 56, 34, 23, 54, 22, 19, 17, 18, 72, 51, 49, 52, 24, 39, 30, 31, 10, 91, 80, 78, 77, 75, 61, 62, 66, 68, 44, 43, 41, 71, 70, 25, 26, 27 };
	auto arr_size = sizeof(arr) / sizeof(arr[0]);

	cout << "Given array is" << endl;
	printArray(arr, arr_size);
	cout << endl << "Size: " << arr_size << endl;

	// Measure sorting performance using high-resolution clock
	auto start = chrono::steady_clock::now();

	mergeSort(arr, 0, arr_size - 1);

	auto end = chrono::steady_clock::now();

	// Print timing results
	cout << "Merge Sort" << endl;
	cout << "Elapsed time in nanoseconds: "
		<< chrono::duration_cast<chrono::nanoseconds>(end - start).count()
		<< " ns" << endl;

	cout << "Elapsed time in microseconds: "
		<< chrono::duration_cast<chrono::microseconds>(end - start).count()
		<< " us" << endl;

	cout << "Elapsed time in milliseconds: "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " ms" << endl;

	// Print the number of merge operations performed
	cout << "Merge operations (steps): " << steps << endl;

	cout << "Sorted array is" << endl;
	printArray(arr, arr_size);
	cout << endl;

	return 0;
}

// This code is contributed by Mayank Tyagi
// This code was revised by Joshua Estes
