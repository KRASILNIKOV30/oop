#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <string_view>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchStr;
	std::string replaceStr;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchStr = argv[3];
	args.replaceStr = argv[4];
	return args;
}

// Переписать на исключения (Исправлено)
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

// Переименовать (Исправлено)
bool FlushFile(std::ofstream& output)
{
	if (!output.flush())
	{
		throw std::runtime_error("Failed to save data on disk");
	}
}
std::string ReplaceString(std::string_view str, std::string const& searchStr, std::string const& replaceStr)
{
	if (searchStr.empty())
	{
		return std::string(str);
	}

	size_t searchStrLength = searchStr.size();
	size_t strLength = str.size();
	std::string result;
	size_t pos = 0;
	while (pos < strLength)
	{
		size_t foundPos = str.find(searchStr, pos);
		// Сделать 2 append (Исправлено)
		result.append(str, pos, foundPos - pos);
		if (foundPos == std::string_view::npos)
		{
			break;
		}
		result.append(replaceStr);
		pos = foundPos + searchStrLength;
	}

	return result;
}

void CopyStreamsWithReplacement(std::string const& inputFileName, std::string const& outputFileName, std::string const& searchStr, std::string const& replaceStr)
{
	std::ifstream input(inputFileName);
	std::ofstream output(outputFileName);
	OpenStreamsErrorHandling(input, output);

	std::string line;
	while (std::getline(input, line))
	{
		if (!(output << ReplaceString(line, searchStr, replaceStr) << std::endl))
		{
			throw std::invalid_argument("Failed to save data on disk");
		}
	}

	if (!input.eof())
	{
		throw std::runtime_error("Error while reading input file");
	}

	FlushFile(output);
}

// Обработать ситуацию, когда поисковая строка пустая
int main(int argc, char* argv[])
{
	// Занести вывод инструкций в ParseArgs (Исправлено)
	auto args = ParseArgs(argc, argv);

	if (!args.has_value())
	{
		return 1;
	}

	try
	{
		// Принимать имена файлов (Исправлено)
		CopyStreamsWithReplacement(args->inputFileName, args->outputFileName, args->searchStr, args->replaceStr);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
