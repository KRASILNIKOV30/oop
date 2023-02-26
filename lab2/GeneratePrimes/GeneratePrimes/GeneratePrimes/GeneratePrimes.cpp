#include <iostream>
#include "GeneratePrimeNumbersSet.h"

int main()
{
    std::set<int> primesSet;
    std::set<int>::iterator iterator;

    int upperBound;
    std::cout << "Enter primes set upper bound: ";
    std::cin >> upperBound;
    primesSet = GeneratePrimeNumbersSet(upperBound);
    for (auto& element : primesSet) {
        std::cout << element << " ";
    }
}

