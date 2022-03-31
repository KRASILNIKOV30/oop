// HTMLDecoder.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "HTMLDecode.h"

int main()
{
    std::string html = "";
    char ch;
    while (std::cin >> ch)
    {
        html.push_back(ch);
    }
    std::cout << html << std::endl;
}
