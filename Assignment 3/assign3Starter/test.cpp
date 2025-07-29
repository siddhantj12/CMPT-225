// testDynamicHeap.cpp
// Automated tests for DynamicHeap (Assignment #3)

#include "DynamicHeap.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

void testConstructor() {
    DynamicHeap h;
    assert(h.getSize() == 0);
    cout << "[PASS] Constructor initializes empty heap\n";
}

void testInsertAndRemove() {
    DynamicHeap h;
    vector<int> input = {5, 1, 3, 4, 2};
    for (int x : input) h.insert(x);
    assert(h.getSize() == (int)input.size());

    vector<int> result;
    while (h.getSize() > 0) result.push_back(h.removeMax());
    vector<int> expected = {5, 4, 3, 2, 1};
    assert(result == expected);
    // Removing from empty should return -1
    assert(h.removeMax() == -1);

    cout << "[PASS] insert() and removeMax() maintain max-heap order and handle empty\n";
}

void testCopyAndAssignment() {
    // Build original heap
    DynamicHeap orig;
    for (int i = 1; i <= 10; ++i) orig.insert(i);

    // Capture expected sequence
    DynamicHeap temp = orig;
    vector<int> expected;
    while (temp.getSize() > 0) expected.push_back(temp.removeMax());

    // Test copy constructor
    DynamicHeap copy(orig);
    vector<int> seqCopy;
    while (copy.getSize() > 0) seqCopy.push_back(copy.removeMax());
    assert(seqCopy == expected);

    // Test copy-assignment
    DynamicHeap assign;
    assign = orig;
    vector<int> seqAssign;
    while (assign.getSize() > 0) seqAssign.push_back(assign.removeMax());
    assert(seqAssign == expected);

    cout << "[PASS] Copy constructor and assignment operator produce identical heaps\n";
}

void testResizing() {
    DynamicHeap h;
    // Trigger growth beyond initial capacity (7)
    for (int i = 1; i <= 20; ++i) h.insert(i);
    assert(h.getSize() == 20);

    // Remove to trigger shrink (size < capacity / 4)
    for (int i = 0; i < 13; ++i) h.removeMax();
    // After 13 removals, size should be 7
    assert(h.getSize() == 7);

    // Further operations continue to work
    h.insert(99);
    assert(h.getSize() == 8);
    int max = h.removeMax();
    assert(max == 99);

    cout << "[PASS] Dynamic resizing on insert/remove works\n";
}

void testPrintHeap() {
    DynamicHeap h;
    for (int i = 1; i <= 7; ++i) h.insert(i);
    cout << "\n--- printHeap() output ---\n";
    h.printHeap(cout);
    cout << "--- end of printHeap() output ---\n";
    cout << "[INFO] Manually verify printHeap visually\n";
}

int main() {
    cout << "Running DynamicHeap tests...\n";
    testConstructor();
    testInsertAndRemove();
    testCopyAndAssignment();
    testResizing();
    testPrintHeap();
    cout << "All tests passed!\n";
    return 0;
}
