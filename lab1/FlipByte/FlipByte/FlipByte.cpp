#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

using namespace std;

struct Args
{
	string inputByte;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		return nullopt;
	}
	Args args;
	args.inputByte = argv[1];
	return args;
}

bool ProcessArgError(const optional<Args>& args)
{
	if (!args)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: copyfile.exe <input byte>\n";
		return false;
	}
	return true;
}

bool ParseInput(const std::string stringByte, short &byte)
{
	try
	{
		size_t* idx = 0;
		byte = std::stoi(stringByte, idx, 10);
		if (byte < 0 || byte > 255)
		{
			std::cout << "Invalid input\n";
			std::cout << "Value must be between 0 and 255\n";
			return false;
		}
		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return false;
	}
}

int ReversByte(int byte) 
{
	byte = (byte & 0b01010101) << 1 | (byte & 0b10101010) >> 1;
	byte = (byte & 0b00110011) << 2 | (byte & 0b11001100) >> 2;
	byte = (byte & 0b00001111) << 4 | (byte & 0b11110000) >> 4;
	return byte;
}


int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!ProcessArgError(args))
	{
		return 1;
	};

	short byte = 0;

	if (!ParseInput(args->inputByte, byte))
	{
		return 1;
	};

	std::cout << byte << endl;

	std::cout << ReversByte(byte) << endl;

	return 0;
}
