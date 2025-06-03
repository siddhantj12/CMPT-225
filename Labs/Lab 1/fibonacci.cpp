// C++ program to illustrate time point
// and system clock functions
#include <chrono>
#include <ctime>
#include <iostream>

// Function to calculate
// Fibonacci series
long fibonacci(unsigned n) {
  if (n < 2)
    return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
  // Using time point and system_clock
  std::chrono::time_point<std::chrono::system_clock> start, end;

  start = std::chrono::system_clock::now();
  std::cout << "f(42) = " << fibonacci(42) << '\n';
  end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end - start;

  std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
