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
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchStr = argv[3];
	args.replaceStr = argv[4];
	return args;
}

std::string ReplaceString(std::string_view str, std::string const& searchStr, std::string const& replaceStr)
{
	size_t searchStrLength = searchStr.size();
	size_t strLength = str.size();
	std::string result;
	size_t pos = 0;
	while (pos < strLength)
	{
		size_t foundPos = str.find(searchStr, pos);
		if (foundPos == std::string_view::npos)
		{
			return result.append(str, pos);
		}
		result.append(str, pos, foundPos - pos);
		result.append(replaceStr);
		pos = foundPos + searchStrLength;
	}

	return result;
}

bool CopyStreamWithReplacement(std::istream& input, std::ostream& output, std::string const& searchStr, std::string const& replaceStr)
{
	std::string line;
	while (std::getline(input, line))
	{
		if (!(output << ReplaceString(line, searchStr, replaceStr) << std::endl))
		{
			std::cout << "Failed to save data on disk" << std::endl;
			return false;
		}
	}
	return true;
}

bool OpenStreamsErrorHandling(std::ifstream& input, std::ofstream& output)
{

	if (!input.is_open())
	{
		std::cout << "Failed to open file for reading\n";
		return false;
	}
	if (!output.is_open())
	{
		std::cout << "Failed to open file for writing\n";
		return false;
	}
	return true;
}

bool SaveErrorHandling(std::ofstream& output)
{
	if (!output.flush())
	{
		std::cout << "Failed to save data on disk\n";
		return false;
	}
	return true;
}

bool ProcessArgError(const std::optional<Args>& args)
{
	if (!args.has_value())
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!ProcessArgError(args))
	{
		return 1;
	}

	std::ifstream input(args->inputFileName);
	std::ofstream output(args->outputFileName);

	if (!OpenStreamsErrorHandling(input, output))
	{
		return 1;
	}


	if (!CopyStreamWithReplacement(input, output, args->searchStr, args->replaceStr))
	{
		return 1;
	}

	if (!SaveErrorHandling(output))
	{
		return 1;
	}

	return 0;
}
