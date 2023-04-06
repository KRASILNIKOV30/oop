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
			//(выяснил) TODO: выяснить, зачем эта переменная (size_t* idx = 0;) нужна 
			key = std::stoi(argv[3], 0, 10);
		}
		catch (const std::exception& e)
		{
			//(Исправлено) TODO: лучше логироовать ошибку понятным языком 
			cout << "key must be number" << endl;
			return std::nullopt;
		}
		//(Исправлено) TODO: вынести в константу 
		if (key < MIN_KEY_VALUE || key > MAX_KEY_VALUE)
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

	char CryptChar(char ch, uint8_t key)
	{
		ch = ch ^ key;
		int result = 0b00000000;
		result = result | (ch & 0b10000000) >> 2;
		result = result | (ch & 0b01100000) >> 5;
		result = result | (ch & 0b00011000) << 3;
		result = result | (ch & 0b00000111) << 2;

		return result;
	}

	bool CryptStreams(ifstream& input, ofstream& output, const uint8_t key)
	{
		char ch;
		while (input.get(ch))
		{
			if (!output.put(CryptChar(ch, key)))
			{
				cout << "Failed to save data on disk" << endl;
				return false;
			}
		}
		return true;
	}

	bool AreStreamsOpen(ifstream& input, ofstream& output)
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

	//(Исправлено) TODO: непонятно, что возвращает метод.
	//(Исправлено) TODO: убрать дублирование логов
	if (!args)
	{
		return 1;
	}

	ifstream input(args->inputFileName, ios::binary | ios::in);

	ofstream output(args->outputFileName, ios::binary | ios::out);

	//(Исправлено) TODO: не хватает глагола в названии
	if (!AreStreamsOpen(input, output))
	{
		return 1;
	}

	if (!CryptStreams(input, output, args->key))
	{
		return 1;
	}
	//(Исправлено) TODO: не хватает глагола в названии
	if (!TrySave(output))
	{
		return 1;
	}

	return 0;
}
