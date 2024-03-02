#include <iostream>
#include <optional>
#include <fstream>
#include "ExpandTemplate.h"

struct Args
{
    std::string inputFilePath;
    std::string outputFilePath;
    TemplateParams params;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Invalid argument count\n"
            << "Usage: expand_template.exe <inputFile.txt> <outputFile.txt> [<param> <value> [<param> <value> ...]]\n";
        return std::nullopt;
    }
    Args args;
    args.inputFilePath = argv[1];
    args.outputFilePath = argv[2];
    TemplateParams params;
    for (size_t i = 3; i <= argc - 2; i += 2)
    {
        params.emplace(argv[i], argv[i + 1]);
    }
    args.params = params;

    return args;
}

void CopyAndExpandWithParams(std::istream& input, std::ostream& output, TemplateParams const& params)
{
    std::string line;
    while (std::getline(input, line))
    {
        output << ExpandTemplate(line, params);
    }
}

void OpenStreamsErrorHandling(std::ifstream& input, std::ofstream& output)
{

    if (!input.is_open())
    {
        throw std::invalid_argument("Failed to open file for reading");
    }
    if (!output.is_open())
    {
        throw std::invalid_argument("Failed to open file for writing");
    }
}

bool CopyAndExpandWithParams(std::string& inputFilePath, std::string& outputFilePath, TemplateParams const& params)
{
    std::ifstream input(inputFilePath);
    std::ofstream output(outputFilePath);
    OpenStreamsErrorHandling(input, output);

    CopyAndExpandWithParams(input, output, params);

    if (!input.eof())
    {
        throw std::runtime_error("Error while reading input file");
    }
    if (!output.flush())
    {
        throw std::runtime_error("Failed to save data on disk");
    }

    return true;
}


int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return EXIT_FAILURE;
    }

    if (!CopyAndExpandWithParams(args->inputFilePath, args->outputFilePath, args->params))
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}