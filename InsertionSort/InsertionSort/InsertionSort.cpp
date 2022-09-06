// C++ program for insertion sort

#include <iostream>
#include <ctime>
#include <chrono>
#include <Windows.h>


using namespace std;

int steps = 0;

// Function to sort an array using 
// insertion sort
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1],  
        // that are greater than key, to one 
        // position ahead of their 
        // current position
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
            steps++;
        }
        arr[j + 1] = key;
    }
}

// A utility function to print an array 
// of size n 
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Driver code
int main()
{
    //int arr[] = { 12, 11, 13, 5, 6, 7,15,3,9,21,15, 1, 90,56,34 };
    //int arr[] = { 12, 11, 13, 5, 6, 7,15,3,9,21,15, 1, 90,56,34, 23, 54, 22, 19,17,18,72,51,49,52,24,39,30,31 ,10 };
    //int arr[] = { 12, 11, 13, 5, 6, 7,15,3,9,21,15, 1, 90,56,34, 23, 54, 22, 19,17,18,72,51,49,52,24,39,30,31 ,10,91,80,78,77,75 };
    //int arr[] = { 12, 11, 13, 5, 6, 7,15,3,9,21,15, 1, 90,56,34, 23, 54, 22, 19,17,18,72,51,49,52,24,39,30,31 ,10,91,80,78,77,75,61,62,66,68,44 };
    int arr[] = { 12, 11, 13, 5, 6, 7,15,3,9,21,15, 1, 90,56,34, 23, 54, 22, 19,17,18,72,51,49,52,24,39,30,31 ,10,91,80,78,77,75,61,62,66,68,44,43,41 ,71,70,25 };
    //int arr[] = { 12, 11, 13, 5, 6, 7,15,3,9,21,15, 1, 90,56,34, 23, 54, 22, 19,17,18,72,51,49,52,24,39,30,31 ,10,91,80,78,77,75,61,62,66,68,44,43,41 ,71,70,25,26,27};
    int N = sizeof(arr) / sizeof(arr[0]);
    printArray(arr, N);

    auto start = chrono::steady_clock::now();

    insertionSort(arr, N);

    auto end = chrono::steady_clock::now();
    cout << "Insertion  Sort" << endl;
    cout << "Elapsed time in nanoseconds: "
        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
        << " ns" << endl;

    cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;

    cout << "Elapsed time in milliseconds: "
        << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << " ms" << endl;

    cout << steps << endl;

    printArray(arr, N);

    return 0;
}
// This is code is contributed by rathbhupendra