#include <iostream>
#include <set>
#include <vector>

namespace {
	void InitVector(std::vector<bool>& vector, const int upperBound) {
		for (int i = 0; i <= upperBound; i++) {
			vector.push_back(true);
		}
		vector[0] = vector[1] = false;
	}
	
	void SiftVector(std::vector<bool>& vector, const int upperBound) {
		for (int i = 2; i * i < upperBound; i++) {
			if (vector[i]) {
				for (int j = i * 2; j <= upperBound; j += i) {
					vector[j] = false;
				}
			}
		}
	}

	std::set<int> GetPrimesSetFromVector(std::vector<bool>& vector, const int upperBound) {
		std::set<int> primesSet = {};
		for (int i = 2; i <= upperBound; i++) {
			if (vector[i]) {
				primesSet.insert(i);
			}
		}
		return primesSet;
	}
}

std::set<int> GeneratePrimeNumbersSet(int upperBound) {
	std::set<int> primesSet = {};
	if (upperBound < 2) {
		return primesSet;
	}
	std::vector<bool> vector;
	vector.reserve(upperBound);
	InitVector(vector, upperBound);
	SiftVector(vector, upperBound);
	primesSet = GetPrimesSetFromVector(vector, upperBound);
	return primesSet;
}