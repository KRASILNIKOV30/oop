#include <iostream>
#include <fstream>
#include <optional>
#include <string>

using namespace std;

struct Args
{
	string inputFileName;
	string outputFileName;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		return nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	return args;
}

bool CopyStreams(istream& input, ostream& output)
{
	char ch;
	while (input.get(ch))
	{
		if (!output.put(ch))
		{
			cout << "Failed to save data on disk\n";
			return false;
		}
	}
	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: copyfile.exe <input file> <output file>\n";
		return 1;
	}

	ifstream input(args->inputFileName);
	if (!input.is_open())
	{
		cout << "Failed to open " << args->inputFileName << " for reading\n";
		return 1;
	}

	ofstream output(args->outputFileName);
	if (!output.is_open())
	{
		cout << "Failed to open " << args->outputFileName << " for writing\n";
		return 1;
	}

	if (!CopyStreams(input, output))
		return 1;

	if (!output.flush()) 
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}

	return 0;
}
