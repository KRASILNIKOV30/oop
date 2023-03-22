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
		size_t* idx = 0;//TODO: выяснить, зачем эта переменная нужна
		key = std::stoi(argv[3], idx, 10);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what(); //TODO: лучше логироовать ошибку понятным языком
		return std::nullopt;
	}
	//TODO: вынести в константу
	if (key < 0 || key > 255)
	{
		std::cout << "Invalid input\n";//TODO: use const EOLN
		std::cout << "Key must be between 0 and 255\n"; //TODO: выводить логи тоже с помощью констант
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
	//TODO: убрать дублирование логов
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

	//TODO: непонятно, что возвращает метод.
	if (!ProcessArgError(args))
	{
		return 1;
	}

	ifstream input(args->inputFileName, ios::binary | ios::in);

	ofstream output(args->outputFileName, ios::binary | ios::out);

	//TODO: не хватает глагола в названии
	if (!OpenStreamsErrorHandling(input, output))
	{
		return 1;
	}

	if (!CryptStreams(input, output, args->key))
	{
		return 1;
	}
	//TODO: не хватает глагола в названии
	if (!SaveErrorHandling(output))
	{
		return 1;
	}

	return 0;
}
