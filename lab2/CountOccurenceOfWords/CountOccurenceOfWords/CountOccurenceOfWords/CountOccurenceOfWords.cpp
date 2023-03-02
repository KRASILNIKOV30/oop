#include <iostream>
#include <map>
#include <algorithm>

namespace {
    std::string StrToLower(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(),
            [](unsigned char c) { return std::tolower(c); }
        );
        return str;
    }

    void PrintMap(std::map<std::string, int> map) {
        for (const auto& item : map) {
            std::cout << item.first << ' ' << item.second << std::endl;
        }
    }
}

void CountOccurenceOfWords(std::istream& input) {
    std::map<std::string, int> wordsMap;
    std::string word;
    while (input >> word) {
        wordsMap[StrToLower(word)]++;
    }
    PrintMap(wordsMap);
}


