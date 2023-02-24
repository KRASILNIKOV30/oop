#include <iostream>
#include <set>
#include <vector>

namespace {
	void initVector(std::vector<bool>& vector, const int upperBound) {
		for (int i = 0; i <= upperBound; i++) {
			vector.push_back(true);
		}
		vector[0] = vector[1] = false;
	}
}

std::set<int> GeneratePrimeNumbersSet(int upperBound) {
	std::set<int> primesSet = {};

	if (upperBound < 2) {
		return primesSet;
	}

	std::vector<bool> vector;
	initVector(vector, upperBound);
	int j;
	for (int i = 2; i * i < upperBound; i++) {
		if (vector[i]) {
			for (j = i * 2; j <= upperBound; j += i) {
				vector[j] = false;
			}
		}
	}

	for (int i = 2; i <= upperBound; i++) {
		if (vector[i]) {
			primesSet.insert(i);
		}
	}

	return primesSet;
}