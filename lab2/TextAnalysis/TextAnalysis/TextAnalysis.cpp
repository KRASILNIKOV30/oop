#include <iostream>
#include <map>
#include <algorithm>

namespace {
    std::string str_tolower(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(),
            [](unsigned char c) { return std::tolower(c); }
        );
        return str;
    }
}

void TextAnalysis(std::istream &input) {
    std::map<std::string, int> map;
    std::map<std::string, int>::iterator iterator;
    std::string word;
    while (input >> word) {
        word = str_tolower(word);
        iterator = map.find(word);
        if (iterator != map.end()) {
            iterator->second++;
        } else {
            map.insert({ word, 1 });
        }
        if (input.eof()) {
            break;
        }
    }

    for (iterator = map.begin(); iterator != map.end(); ++iterator) {
        std::cout << iterator->first << ' ' << iterator->second << std::endl;
    }
}


