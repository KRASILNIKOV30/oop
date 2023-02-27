﻿#include <iostream>
#include <map>
#include <algorithm>

namespace {
    std::string str_tolower(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(),
            [](unsigned char c) { return std::tolower(c); }
        );
        return str;
    }

    void printMap(std::map<std::string, int> map) {
        std::map<std::string, int>::iterator iterator;
        for (iterator = map.begin(); iterator != map.end(); ++iterator) {
            std::cout << iterator->first << ' ' << iterator->second << std::endl;
        }
    }
}

void TextAnalysis(std::istream &input) {
    std::map<std::string, int> wordsMap;
    std::map<std::string, int>::iterator iterator;
    std::string word;
    while (input >> word) {
        word = str_tolower(word);
        iterator = wordsMap.find(word);
        if (iterator != wordsMap.end()) {
            iterator->second++;
        } else {
            wordsMap.insert({ word, 1 });
        }
        if (input.eof()) {
            break;
        }
    }
    printMap(wordsMap);
}


