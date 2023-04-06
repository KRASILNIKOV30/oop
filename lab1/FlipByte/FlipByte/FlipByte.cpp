#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

struct Args
{
	std::uint8_t inputByte;
};

namespace
{
	const int MAX_BYTE_VALUE = 255;
	const int MIN_BYTE_VALUE = 0;

	std::optional<Args> ParseArgs(int argc, char* argv[])
	{
		if (argc != 2)
		{
			std::cout << "Invalid arguments count" << std::endl;
			std::cout << "Usage: copyfile.exe <input byte>" << std::endl;
			return std::nullopt;
		}
		int byte;

		try
		{
			byte = std::stoi(argv[1], 0, 10);
		}
		catch (const std::exception& e)
		{
			std::cout << "byte must be a number" << std::endl;
			return std::nullopt;
		}

		if (byte < MIN_BYTE_VALUE || byte > MAX_BYTE_VALUE)
		{
			std::cout << "Invalid input" << std::endl;
			std::cout << "Value must be between " << MIN_BYTE_VALUE << " and " <<  MAX_BYTE_VALUE << std::endl;
			return std::nullopt;
		}
		Args args = {byte};
		return args;
	}

	int ReversByte(uint8_t byte)
	{
		byte = (byte & 0b01010101) << 1 | (byte & 0b10101010) >> 1;
		byte = (byte & 0b00110011) << 2 | (byte & 0b11001100) >> 2;
		byte = (byte & 0b00001111) << 4 | (byte & 0b11110000) >> 4;
		return byte;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	std::cout << ReversByte(args->inputByte) << std::endl;

	return 0;
}
