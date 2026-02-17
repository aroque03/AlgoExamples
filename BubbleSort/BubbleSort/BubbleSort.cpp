// =============================================================================
// Bubble Sort - A Simple Comparison-Based Sorting Algorithm
// =============================================================================
//
// Overview:
//   Bubble Sort repeatedly steps through the list, compares adjacent elements,
//   and swaps them if they are in the wrong order. The pass through the list is
//   repeated until the list is sorted. The algorithm gets its name because
//   smaller elements "bubble" to the top of the list with each iteration.
//
// How it works:
//   1. Start at the beginning of the array.
//   2. Compare each pair of adjacent elements.
//   3. If the left element is greater than the right, swap them.
//   4. After each full pass, the largest unsorted element is in its final
//      position at the end of the array.
//   5. Repeat until no swaps are needed (the array is sorted).
//
// Time Complexity:
//   - Best Case:    O(n)   - when the array is already sorted (with optimization)
//   - Average Case: O(n^2) - when elements are in random order
//   - Worst Case:   O(n^2) - when the array is sorted in reverse order
//
// Space Complexity: O(1) - sorts in place, only uses a constant amount of
//                          extra memory for the temporary swap variable.
//
// Stability: Stable - equal elements maintain their relative order because
//            we only swap when strictly greater (not greater-or-equal).
//
// =============================================================================

#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

// Global step counter to track the number of comparisons made during sorting.
// This is useful for analyzing the algorithm's performance on different inputs.
int steps = 0;

// -----------------------------------------------------------------------------
// bubbleSort - Sorts an array of integers in ascending order using Bubble Sort.
//
// Parameters:
//   arr[] - the array of integers to be sorted
//   n     - the number of elements in the array
//
// Algorithm:
//   The outer loop runs (n-1) times. After each iteration i, the largest
//   (i+1) elements are guaranteed to be in their correct final positions
//   at the end of the array.
//
//   The inner loop compares adjacent elements from the start of the array
//   up to the last unsorted position (n - i - 1).
//
//   Optimization: A boolean flag 'swapped' detects if no swaps occurred
//   during a pass. If no swaps happened, the array is already sorted and
//   we can terminate early, giving O(n) best-case performance.
// -----------------------------------------------------------------------------
void bubbleSort(int arr[], int n)
{
    bool swapped;

    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;

        // Compare adjacent elements up to the last unsorted position.
        // After pass i, the last i elements are already sorted.
        for (int j = 0; j < n - i - 1; j++)
        {
            steps++; // Count each comparison

            if (arr[j] > arr[j + 1])
            {
                // Swap arr[j] and arr[j+1] using a temporary variable
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                swapped = true;
            }
        }

        // Early termination: if no swaps occurred in this pass,
        // the array is already sorted and we can stop.
        if (!swapped)
            break;
    }
}

// -----------------------------------------------------------------------------
// printArray - Utility function to print all elements of an array.
//
// Parameters:
//   arr[] - the array to print
//   n     - the number of elements in the array
// -----------------------------------------------------------------------------
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// -----------------------------------------------------------------------------
// Driver code - Demonstrates Bubble Sort with performance measurement.
//
// The program:
//   1. Prints the unsorted array.
//   2. Runs Bubble Sort while measuring elapsed time.
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
    int N = sizeof(arr) / sizeof(arr[0]);

    cout << "Given array is" << endl;
    printArray(arr, N);
    cout << "Size: " << N << endl;

    // Measure sorting performance using high-resolution clock
    auto start = chrono::steady_clock::now();

    bubbleSort(arr, N);

    auto end = chrono::steady_clock::now();

    // Print timing results
    cout << "Bubble Sort" << endl;
    cout << "Elapsed time in nanoseconds: "
        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
        << " ns" << endl;

    cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " us" << endl;

    cout << "Elapsed time in milliseconds: "
        << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << " ms" << endl;

    // Print the number of comparisons performed
    cout << "Comparisons (steps): " << steps << endl;

    cout << "Sorted array is" << endl;
    printArray(arr, N);

    return 0;
}
