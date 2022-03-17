#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

bool ParseFloatsToVector(std::istream& input, std::vector<float>& v);
void MultElementsByMin(std::vector<float>& v);
