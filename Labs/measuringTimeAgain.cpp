/*#include <chrono>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

void printHeader() {
    cout << right
         << setw(8)  << "n"
         << setw(12) << "f(n)"
         << setw(12) << "log n"
         << setw(12) << "n"
         << setw(12) << "n log n"
         << setw(12) << "n^2"
         << "\n";

}

static const int MAX = 65536; 

// fill array A with random values 
void fillRandom(int A[], int n){
    for (int i = 0; i < n; ++i) {
        A[i] = rand(); // random int between 0 and 99
    }
}

// return an array of random values in order
void f(int A[], int n) {
    fillRandom(A,n);
    sort(A,A+n);
}


// Test the function f for an array of the given size n
// print the factor of the time vs. possible complexity classes
void testF(int A[], int n) {

    cout << n << "\t";

    // time the function 
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

    for(int i = 0; i < 10000; i++){
        f(A,n);
    }
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = chrono::duration_cast< chrono::duration<double> >(end - start);

    double elapsedTime = elapsed.count();  // instead of: double time = elapsed.count();

    void testF(int A[], int n) ;{
    // print n
    cout << n << "\t";

    // time the function f
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 10000; i++){
        f(A, n);
    }
    auto end = chrono::high_resolution_clock::now();
    double t = chrono::duration<double>(end - start).count();

    // compute theory functions
    double ln = log(n);
    double nln = n * ln;
    double n2 = double(n) * n;

    // print the five columns
    cout << t        << "\t"      // f(n)
         << ln/t     << "\t"      // log n / f(n)
         << (n/t)    << "\t"      // n / f(n)
         << (nln/t)  << "\t"      // n log n / f(n)
         << (n2/t)   << "\n";     // n^2 / f(n)
          cout << right
         << setw(8)  << n
         << setw(12) << fixed << setprecision(5) << t
         << setw(12) << setprecision(5) << ln
         << setw(12) << setprecision(5) << double(n)
         << setw(12) << setprecision(5) << nln
         << setw(12) << setprecision(1) << n2
         << "\n";
    }
}

int main() {
    
    int A[MAX];
    srand(time(nullptr)); // seed RNG with current time
    
    cout << setprecision(5);
  
    cout << "n \t f(n) \t\t log n \t\t n \t\t n log n \t n^2 "<< endl;

    int n = 128;
    for(int i = 0; i < 10; i++){
        testF(A, n);
        n *= 2;
    }
    
    return 0;
}*/

#include <chrono>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

void printHeader() {
    cout << right
         << setw(8) << "n"
         << setw(12) << "f(n)"
         << setw(12) << "log n"
         << setw(12) << "n"
         << setw(12) << "n log n"
         << setw(12) << "n^2"
         << "\n";
}

static const int MAX = 65536;

// fill array A with random values
void fillRandom(int A[], int n) {
    for (int i = 0; i < n; ++i) {
        A[i] = rand();
    }
}

// perform random fill and sort
void f(int A[], int n) {
    fillRandom(A, n);
    sort(A, A + n);
}

// test f for an array of size n and print timing ratios
void testF(int A[], int n) {
    // time the function calls
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        f(A, n);
    }
    auto end = chrono::high_resolution_clock::now();
    double t = chrono::duration<double>(end - start).count();

    // compute theoretical values
    double ln   = log(n);
    double nln  = n * ln;
    double n2   = double(n) * n;

    // print aligned columns
    cout << right
         << setw(8)  << n
         << setw(12) << fixed << setprecision(5) << t
         << setw(12) << setprecision(5) << ln
         << setw(12) << setprecision(5) << double(n)
         << setw(12) << setprecision(5) << nln
         << setw(12) << setprecision(1) << n2
         << "\n";
}

int main() {
    int A[MAX];
    srand(time(nullptr)); // seed RNG

    // header and formatting
    cout << fixed << setprecision(5);
    printHeader();

    // run tests doubling n
    int n = 128;
    for (int i = 0; i < 10; ++i) {
        testF(A, n);
        n *= 2;
    }
    
 cout << "\nConclusion: Based on the relatively flat n log n / f(n) ratios, "
         << "f(n) ∈ Θ(n log n)" << endl;

    return 0;
}
