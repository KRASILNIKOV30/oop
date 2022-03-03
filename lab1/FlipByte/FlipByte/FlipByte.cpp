#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

struct Args
{
	std::uint8_t inputByte;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: copyfile.exe <input byte>\n";
		return std::nullopt;
	}
	int byte;

	try
	{
		size_t* idx = 0;
		byte = std::stoi(argv[1], idx, 10);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return std::nullopt;
	}

	if (byte < 0 || byte > 255)
	{
		std::cout << "Invalid input\n";
		std::cout << "Value must be between 0 and 255\n";
		return std::nullopt;
	}
	Args args;
	args.inputByte = byte;
	return args;
}

int ReversByte(uint8_t byte) 
{
	byte = (byte & 0b01010101) << 1 | (byte & 0b10101010) >> 1;
	byte = (byte & 0b00110011) << 2 | (byte & 0b11001100) >> 2;
	byte = (byte & 0b00001111) << 4 | (byte & 0b11110000) >> 4;
	return byte;
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
