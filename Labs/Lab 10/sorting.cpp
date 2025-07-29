#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>
using namespace std;
using namespace chrono;

// ------------------ Insertion sort ------------------
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Move elements greater than key one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // Insert key into the correct location
        arr[j + 1] = key;
    }
}

// ------------------ Quicksort ------------------
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // using last element as pivot
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j)
            return j;

        swap(arr[i], arr[j]);
    }
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // Partition the array
        int pi = partition(arr, low, high);

        // Recursively sort the subarrays
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSort(vector<int>& arr){
    quickSort(arr, 0, arr.size()-1);
}



// ------------------ Heap Sort ------------------
void heapify(vector<int>& arr){
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0 && arr[j] > arr[(j - 1) / 2]) {
            swap(arr[j], arr[(j - 1) / 2]);
            j = (j - 1) / 2;
        }
    }
}

void removeMax(vector<int>& arr, int i){
    swap(arr[0], arr[i - 1]); // move max to the end
    int j = 0;
    bool done = false;

    while (!done) {
        int left = 2 * j + 1;
        int right = 2 * j + 2;
        int largest = j;

        if (left < i - 1 && arr[left] > arr[largest])
            largest = left;
        if (right < i - 1 && arr[right] > arr[largest])
            largest = right;

        if (largest == j)
            done = true;
        else {
            swap(arr[j], arr[largest]);
            j = largest;
        }
    }
}

void heapSort(vector<int>& arr){
    int n = arr.size();
    heapify(arr);

    for (int i = n; i > 1; i--) {
        removeMax(arr, i);
    }
}


// ------------------ Test Framework ------------------
void testSort(void(*sortFunc)(vector<int>&), vector<int> data, const string& label, const string& inputType) {
    auto start = high_resolution_clock::now();
    sortFunc(data);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    
    // Store or print formatted output
    cout << "| " << left << setw(15) << label
         << "| " << left << setw(15) << inputType
         << "| " << right << setw(8) << duration.count() << " ms |\n";
}

void printTitle(){
    cout << "\n"
     << "+-----------------+-----------------+-----------+\n"
     << "| Algorithm       | Input Type      | Time      |\n"
     << "+-----------------+-----------------+-----------+\n";
}

int main() {
    const int SIZE = 100000;

    // YOUR WORK IS HERE
    // fill these three arrys so that each sorting algotihm can be the best

    // fill these three arrays so that each sorting algorithm hits its best case
    vector<int> firstType(SIZE);
    vector<int> secondType(SIZE);
    vector<int> thridType(SIZE);

    // 1) Best case for Insertion Sort: ascending order
    for (int i = 0; i < SIZE; ++i) {
        firstType[i] = i;
    }

    // 2) Best/average case for Quicksort: random values
    std::mt19937_64 rng(
        std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(0, SIZE);
    for (int i = 0; i < SIZE; ++i) {
        secondType[i] = dist(rng);
    }

    // 3) Worst case for both Insertion and Quicksort: descending order
    for (int i = 0; i < SIZE; ++i) {
        thridType[i] = SIZE - i - 1;
    }

    printTitle();
    testSort(insertionSort, firstType, "Insertion Sort", "Ascending");
    testSort(quickSort, firstType, "Quicksort", "Ascending");
    testSort(heapSort, firstType, "Heapsort", "Ascending");

    printTitle();
    testSort(insertionSort, secondType, "Insertion Sort ", "Random");
    testSort(quickSort, secondType, "Quicksort", "Random");
    testSort(heapSort, secondType, "Heapsort", "Random");

    printTitle();
    testSort(insertionSort, thridType, "Insertion Sort", "Descending");
    testSort(quickSort, thridType, "Quicksort", "Descending");
    testSort(heapSort, thridType, "Heapsort", "Descending");

    return 0;
}
