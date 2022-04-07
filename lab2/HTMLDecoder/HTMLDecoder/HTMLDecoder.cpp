// HTMLDecoder.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "HTMLDecode.h"

int main()
{
    std::string html;
    while (!std::cin.eof())
    {
        getline(std::cin, html);
        std::cout << HtmlDecode(html) << std::endl;
    }
}
