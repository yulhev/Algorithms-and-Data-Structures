#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

int bubbleSortSwaps = 0;
int shellSortSwaps = 0;

// Bubble Sort
void bubbleSort(int arr[], int n) {
    bubbleSortSwaps = 0; // Reset swap count for Bubble Sort
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
                bubbleSortSwaps++;
            }
        }
        if (!swapped) break;
    }
}

// Shell Sort
void shellSort(int arr[], int n) {
    shellSortSwaps = 0; // Reset swap count for Shell Sort
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
                shellSortSwaps++;
            }
            arr[j] = temp;
        }
    }
}

// Function to generate different data types
void generateData(int arr[], int n, string type) {
    if (type == "unsorted") {
        for (int i = 0; i < n; ++i) {
            arr[i] = rand() % n + 1;
        }
    }
    else if (type == "sorted") {
        for (int i = 0; i < n; ++i) {
            arr[i] = i + 1;
        }
    }
    else if (type == "reverse-sorted") {
        for (int i = 0; i < n; ++i) {
            arr[i] = n - i;
        }
    }
}

int main() {
    srand(time(nullptr));

    // Test data sizes
    int dataSizes[] = { 5000, 10000, 50000, 100000 };
    string dataTypes[] = { "unsorted", "reverse-sorted", "sorted" };
    string algorithms[] = { "Bubble Sort", "Shell Sort" };

    for (string dataType : dataTypes) {
        cout << "Data Type: " << dataType << endl;
        for (int dataSize : dataSizes) {
            int* arr = new int[dataSize];

            // Generate test data
            generateData(arr, dataSize, dataType);

            for (string algorithm : algorithms) {
                int* tempArr = new int[dataSize];
                copy(arr, arr + dataSize, tempArr);

                auto start = high_resolution_clock::now();

                

                // Sort based on selected algorithm
                if (algorithm == "Bubble Sort") {
                    bubbleSort(tempArr, dataSize);
                    cout << "Bubble Sort swaps for " << dataSize << " elements: " << bubbleSortSwaps << endl;
                }
                else if (algorithm == "Shell Sort") {
                    shellSort(tempArr, dataSize);
                    cout << "Shell Sort swaps for " << dataSize << " elements: " << shellSortSwaps << endl;
                }
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<milliseconds>(stop - start);

                cout << algorithm << " on " << dataSize << " elements: " << duration.count() << "ms" << endl;
        

                delete[] tempArr;
            }

            delete[] arr;
        }
        cout << "------------------------" << endl;
    }

    return 0;
}
