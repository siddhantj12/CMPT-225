// Student Name: 
// CMPT 225 Assignment #3
//Created by Jocelyn Minns, 
//Based on content from Chris Schmidt, please do not make available online
#include "DynamicHeap.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
using std::cout, std::cin, std::endl;

//A max-heap stored as an array which will be reallocated with increased or decreased size as appropriate
//The initial capacity is 7 data values with index 0 storing how many values are actually in the heap

//IMPLEMENT
//set up the heap array
DynamicHeap::DynamicHeap() {
    heap = new int[capacity + 1];
    heap[0] = 0;
}

//IMPLEMENT
//free storage
DynamicHeap::~DynamicHeap() {
    delete[] heap;
    heap = nullptr;
    capacity = 0;
}

// Copy constructor: deep copy of heap and capacity
DynamicHeap::DynamicHeap(const DynamicHeap& other) {
    capacity = other.capacity;
    heap = new int[capacity + 1];
    int sz = other.heap[0];
    for (int i = 0; i <= sz; ++i) {
        heap[i] = other.heap[i];
    }
}

// Assignment operator: guard self-assign, then deep copy
DynamicHeap& DynamicHeap::operator=(const DynamicHeap& other) {
    if (this != &other) {
        delete[] heap;
        capacity = other.capacity;
        heap = new int[capacity + 1];
        int sz = other.heap[0];
        for (int i = 0; i <= sz; ++i) {
            heap[i] = other.heap[i];
        }
    }
    return *this;
}

// Return number of stored values
int DynamicHeap::getSize() const {
    return heap[0];
}

// Insert new key into heap, resizing if needed
void DynamicHeap::insert(int key) {
    // grow if full
    if (heap[0] + 1 > capacity) {
        increaseCapacity();
    }
    // insert at end
    heap[++heap[0]] = key;
    // sift up to restore max-heap
    int i = heap[0];
    while (i > 1 && heap[i] > heap[i / 2]) {
        std::swap(heap[i], heap[i / 2]);
        i /= 2;
    }
}

// Remove and return max (root); return -1 if empty
int DynamicHeap::removeMax() {
    if (heap[0] == 0) {
        return -1;
    }
    int maxVal = heap[1];
    // move last to root and shrink size
    heap[1] = heap[heap[0]--];
    // sift down to restore heap
    int i = 1;
    while (true) {
        int left = 2 * i;
        int right = 2 * i + 1;
        int largest = i;
        if (left <= heap[0] && heap[left] > heap[largest]) {
            largest = left;
        }
        if (right <= heap[0] && heap[right] > heap[largest]) {
            largest = right;
        }
        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            i = largest;
        } else {
            break;
        }
    }
    // shrink if less than 1/4 full and above minimum capacity
    if (heap[0] < capacity / 4 && capacity > 7) {
        decreaseCapacity();
    }
    return maxVal;
}

// Double capacity and copy existing data
void DynamicHeap::increaseCapacity() {
    int newCap = capacity * 2 + 1;
    int* newHeap = new int[newCap + 1];
    int sz = heap[0];
    for (int i = 0; i <= sz; ++i) {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
    capacity = newCap;
}

// Halve capacity and copy existing data
void DynamicHeap::decreaseCapacity() {
    int newCap = capacity / 2;
    int* newHeap = new int[newCap + 1];
    int sz = heap[0];
    for (int i = 0; i <= sz; ++i) {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    newHeap[0] = sz;  // maintain size after copying
    heap = newHeap;
    capacity = newCap;
}

// Provided: prints the heap in a tree-like structure
void DynamicHeap::printHeap(std::ostream& out) const {
    int level = 1;
    int items = heap[0];
    int width = (1 << ((int)std::log2(items + 1))) * 2;
        int newline;

    // Check for empty heap
    if (heap[0] == 0) {
        out << "Heap is empty." << std::endl;
        return;
    }

    // header bar
    out << std::setfill('-') << std::setw(width) << "" << std::endl
        << std::setfill(' ');

    newline = 1;
    for (int i = 1; i <= items; i++) {
        out << std::setw(width / (1 << level)) << "";
        out << heap[i] << " ";
        if (i == newline) {
            out << std::endl;
            newline = newline * 2 + 1;
            level++;
        }
        if (newline > items) {
            break;
        }
    }
    out << std::endl << std::endl;
}
