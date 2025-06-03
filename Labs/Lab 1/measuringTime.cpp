#include <array>
#include <chrono>
#include <iomanip>
#include <iostream>
using namespace std;

static const int MAX = 65536; // 2^16

// sum an array using a loop with a static array
int linearSumLoop(const int arr[], int n) {
  int sum = 0;
  for (int i = 0; i < n; i++)
    sum += arr[i];
  return sum;
}

// sum an array using recursion
int linearSumRec(const int arr[], int n) {
  if (n == 0)
    return 0;
  return linearSumRec(arr, n - 1) + arr[n - 1];
}

// sum an array using a loop with an array class
int linearSumLoop(const std::array<int, MAX> &arr, int n) {
  int sum = 0;
  for (int i = 0; i < n; ++i)
    sum += arr[i];
  return sum;
}

void testRec(const int arr[], int n) {

  // 1) Time the loop version
    auto start1 = std::chrono::system_clock::now();
    int sumLoop = linearSumLoop(arr, n);
    auto   end1 = std::chrono::system_clock::now();
    std::chrono::duration<double> durLoop = end1 - start1;

    // 2) Time the recursive version
    auto start2 = std::chrono::system_clock::now();
    int sumRec  = linearSumRec(arr, n);
    auto   end2 = std::chrono::system_clock::now();
    std::chrono::duration<double> durRec = end2 - start2;

      double tLoop = durLoop.count();
    double tRec  = durRec.count();
    double ratio = (tLoop > 0.0 ? tRec / tLoop : 0.0);

    std::cout << n << "\t"
              << tLoop << "\t"
              << tRec  << "\t"
              << ratio << "\n";
  std::chrono::time_point<std::chrono::system_clock> begin, end;
  begin = std::chrono::system_clock::now();
  linearSumLoop(arr, n);
  end = std::chrono::system_clock::now();
  std::chrono::duration<double> time = end - begin;
  std::cout << "linearSumLoop costs " << time.count() << " secs.\n";
  begin = std::chrono::system_clock::now();
  linearSumRec(arr, n);
  end = std::chrono::system_clock::now();
  time = end - begin;
  std::cout << "linearSumRec costs " << time.count() << " secs.\n";
}

void testClass(const int staticA[], const std::array<int, MAX> &classA, int n) {

   // 1a) Time loop on staticA:
    auto start1 = std::chrono::system_clock::now();
    int sumStatic = linearSumLoop(staticA, n);
    auto   end1 = std::chrono::system_clock::now();
    std::chrono::duration<double> durStatic = end1 - start1;

    // 2) Time loop on classA:
    auto start2 = std::chrono::system_clock::now();
    int sumClass = linearSumLoop(classA, n);
    auto   end2 = std::chrono::system_clock::now();
    std::chrono::duration<double> durClass = end2 - start2;
     // 3) Print: n, durStatic, durClass, (durClass / durStatic)
    double tStatic = durStatic.count();
    double tClass  = durClass.count();
    double ratio   = (tStatic > 0.0 ? tClass / tStatic : 0.0);

    std::cout << n << "\t"
              << tStatic << "\t"
              << tClass  << "\t"
              << ratio   << "\n";
  std::chrono::time_point<std::chrono::system_clock> begin, end;
  begin = std::chrono::system_clock::now();
  linearSumLoop(staticA, n);
  end = std::chrono::system_clock::now();
  std::chrono::duration<double> time = end - begin;
  std::cout << "linearSumLoop for static array costs " << time.count()
            << " secs.\n";
  begin = std::chrono::system_clock::now();
  linearSumLoop(classA, n);
  end = std::chrono::system_clock::now();
  time = end - begin;
  std::cout << "linearSumLoop for class array costs " << time.count()
            << " secs.\n";
}

int main() {

  int staticA[MAX];
  array<int, MAX> classA;

  cout << setprecision(8);
  cout << "n \t iterative \t recursive \t difference \n";

  // test iterative versions vs recursive version
  int n = 64;
  for (int i = 0; i < 10; i++) {
    testRec(staticA, n);
    n *= 2;
  }

  cout << "\n\n";

  // test static arrays vs standard library arrays
  cout << "n \t static \t class \t\t difference\n";
  n = 64;
  for (int i = 0; i < 10; i++) {
    testClass(staticA, classA, n);
    n *= 2;
  }

  return 0;
}