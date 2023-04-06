#include <iostream>
#include <fstream>
#include <optional>
#include <string>

using namespace std;

namespace
{
	const int MAX_KEY_VALUE = 255;
	const int MIN_KEY_VALUE = 0;

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
			cout << "Invalid arguments count" << endl;
			return nullopt;
		}

		int key;
		try
		{
			key = std::stoi(argv[3], 0, 10);
		}
		catch (const std::exception& e)
		{
			cout << "key must be number" << endl;
			return std::nullopt;
		}

		if (key < 0 || key > 255)
		{
			cout << "key must be number between " << MIN_KEY_VALUE << " and " << MAX_KEY_VALUE << endl;
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
				cout << "Failed to save data on disk" << endl;
				return false;
			}
		}
		return true;
	}

	bool IsStreamsOpen(ifstream& input, ofstream& output)
	{
		if (!input.is_open())
		{
			cout << "Failed to open file for reading" << endl;
			return false;
		}
		if (!output.is_open())
		{
			cout << "Failed to open file for writing" << endl;
			return false;
		}
		return true;
	}

	bool TrySave(ofstream& output)
	{
		if (!output.flush())
		{
			cout << "Failed to save data on disk" << endl;
			return false;
		}
		return true;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	ifstream input(args->inputFileName, ios::binary | ios::in);

	ofstream output(args->outputFileName, ios::binary | ios::out);

	if (!IsStreamsOpen(input, output))
	{
		return 1;
	}

	if (!DecryptStreams(input, output, args->key))
	{
		return 1;
	}

	if (!TrySave(output))
	{
		return 1;
	}

	return 0;
}
