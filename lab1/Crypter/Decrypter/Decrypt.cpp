#include <iostream>
#include <fstream>
#include <optional>
#include <string>

using namespace std;

struct Args
{
	string inputFileName;
	string outputFileName;
	uint8_t key;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		return nullopt;
	}

	int key;
	try
	{
		size_t* idx = 0;
		key = std::stoi(argv[3], idx, 10);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return std::nullopt;
	}

	if (key < 0 || key > 255)
	{
		std::cout << "Invalid input\n";
		std::cout << "Key must be between 0 and 255\n";
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.key = key;

	return args;
}

char DecryptChar(char ch, uint8_t key)
{
	int result = 0b00000000;
	result = result | (ch & 0b00100000) << 2;
	result = result | (ch & 0b00000011) << 5;
	result = result | (ch & 0b11000000) >> 3;
	result = result | (ch & 0b00011100) >> 2;
	result = result ^ key;

	return result;
}

bool DecryptStreams(ifstream& input, ofstream& output, const uint8_t key)
{
	char ch;
	while (input.get(ch))
	{
		if (!output.put(DecryptChar(ch, key)))
		{
			cout << "Failed to save data on disk\n";
			return false;
		}
	}
	return true;
}

bool OpenStreamsErrorHandling(ifstream& input, ofstream& output)
{

	if (!input.is_open())
	{
		cout << "Failed to open file for reading\n";
		return false;
	}
	if (!output.is_open())
	{
		cout << "Failed to open file for writing\n";
		return false;
	}
	return true;
}

bool SaveErrorHandling(ofstream& output)
{
	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return false;
	}
	return true;
}

bool ProcessArgError(const optional<Args>& args)
{
	if (!args.has_value())
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: crypt.exe <input file> <output file> <key>\n";
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

	ifstream input(args->inputFileName, ios::binary | ios::in);

	ofstream output(args->outputFileName, ios::binary | ios::out);

	if (!OpenStreamsErrorHandling(input, output))
	{
		return 1;
	}

	if (!DecryptStreams(input, output, args->key))
	{
		return 1;
	}

	if (!SaveErrorHandling(output))
	{
		return 1;
	}

	return 0;
}
