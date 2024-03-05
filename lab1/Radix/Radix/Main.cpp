#include <iostream>
#include <optional>
#include <stdlib.h>
#include "Radix.h"

constexpr int DECIMAL = 10;

struct Args
{
    std::string srcNotationStr;
    std::string dstNotationStr;
    std::string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cout << "Invalid arguments count" << std::endl;
        std::cout << "Usage: radix.exe <source notation> <destination notation> <value>" << std::endl;
        return std::nullopt;
    };
    Args args;
    args.srcNotationStr = argv[1];
    args.dstNotationStr = argv[2];
    args.value = argv[3];
    return args;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);

    if (!args.has_value())
    {
        return 1;
    }

    try
    {
        // ��������� � ���� ���� + �������� ��������
        int srcNotation = StringToInt(args->srcNotationStr, DECIMAL);
        int dstNotation = StringToInt(args->dstNotationStr, DECIMAL);
        std::cout << ChangeNotation(srcNotation, dstNotation, args->value) << std::endl;
    }
    catch (std::exception const& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}