#include <iostream>
#include <fstream>
#include <vector>
#include <optional>
#include <string>
#include <array>

namespace 
{
	const char LIVE_CELL = '#';
	const char BOUND = '*';
	const char DEAD_CELL = ' ';
	const int MAX_FIELD_SIZE = 20;

	struct Coordinates {
		int x;
		int y;
	};

	using FieldMatrix = std::array<std::array<char, MAX_FIELD_SIZE>, MAX_FIELD_SIZE>;

	struct Field
	{
		int width;
		int height;
		FieldMatrix matrix;
	};

	struct Args
	{
		std::string inputFileName;
		std::optional<std::string> outputFileName = std::nullopt;
	};
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3 && argc != 2)
	{
		std::cout << "Invalid arguments count" << std::endl;
		std::cout << "Usage: live.exe <input file> [<output file>]" << std::endl;
		return std::nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	if (argc == 3) {
		args.outputFileName = argv[2];
	}

	return args;
}

char GetLiveCellNextState(int neighboursNumber)
{
	if (neighboursNumber == 2 || neighboursNumber == 3)
	{
		return LIVE_CELL;
	}
	else
	{
		return DEAD_CELL;
	}
}

char GetDeadCellNextState(int neighboursNumber)
{
	if (neighboursNumber == 3)
	{
		return LIVE_CELL;
	}
	else
	{
		return DEAD_CELL;
	}
}

int GetFieldWidth(int rowLength)
{
	if (rowLength < MAX_FIELD_SIZE)
	{
		return rowLength;
	}
	return MAX_FIELD_SIZE;
}

char GetCell(Coordinates coords, Field const& field)
{
	if (coords.x < 0 || coords.x >= MAX_FIELD_SIZE || coords.y < 0 || coords.y >= MAX_FIELD_SIZE)
	{
		return DEAD_CELL;
	}

	return field.matrix[coords.x][coords.y];
}

// поменять x y (Исправлено)
Field ReadField(std::string const& inputFileName)
{
	std::ifstream input(inputFileName);
	if (!input.is_open())
	{
		throw std::invalid_argument("Failed to open file for reading");
	}
	Field field{};
	std::string str;
	Coordinates coords = { 0, 0 };
	while (std::getline(input, str))
	{
		if (str[0] != BOUND)
		{
			break;
		}
		field.width = GetFieldWidth(static_cast<int>(str.length()));
		for (coords.y = 0; coords.y < str.length() && coords.y < MAX_FIELD_SIZE; coords.y++)
		{
			field.matrix[coords.x][coords.y] = str[coords.y];
		}
		coords.x++;
		if (coords.x == MAX_FIELD_SIZE)
		{
			field.height = MAX_FIELD_SIZE;
			return field;
		}
	}
	if (!input.eof())
	{
		throw std::runtime_error("Error while reading input file");
	}
	field.height = coords.x;

	return field;
}

int GetCellNeighboursNumber(Coordinates coords, Field const& field)
{
	int result = 0;
	for (int x = coords.x - 1; x <= coords.x + 1; x++)
	{
		for (int y = coords.y - 1; y <= coords.y + 1; y++)
		{
			if (!(x == coords.x && y == coords.y) && GetCell({ x, y }, field) == LIVE_CELL)
			{
				result++;
			}
		}
	}

	return result;
}

// Добавить функцию, которая принимает координаты и поле и вернет клетку (Сделано)
// Вынести чтение (Исправлено)
Field GenerateNextGeneration(Field const& field)
{
	Field result = { field.width, field.height };

	for (int x = 0; x < field.height; x++)
	{
		for (int y = 0; y < field.width; y++)
		{
			int neighboursNumber = GetCellNeighboursNumber({ x, y }, field);
			switch (field.matrix[x][y])
			{
				case BOUND:
					result.matrix[x][y] = BOUND;
					break;
				case LIVE_CELL:
					result.matrix[x][y] = GetLiveCellNextState(neighboursNumber);
					break;
				case DEAD_CELL:
					result.matrix[x][y] = GetDeadCellNextState(neighboursNumber);
					break;
				default:
					result.matrix[x][y] = DEAD_CELL;
					break;
			}
		}	
	}

	return result;
}

// Вынести в структуру Field (Исправлено)
void WriteMatrix(std::ostream& output, Field const& field)
{
	Coordinates coords = { 0, 0 };
	for (coords.x; coords.x < field.height; coords.x++)
	{
		for (coords.y = 0; coords.y < field.width; coords.y++)
		{
			output << field.matrix[coords.x][coords.y];
		}
		output << std::endl;
	}

	if (!output.flush())
	{
		throw std::runtime_error("Failed to save data on disk");
	}
}

void WriteResult(std::optional<std::string> outputFileName, Field const& outField)
{
	if (!outputFileName.has_value())
	{
		WriteMatrix(std::cout, outField);
		return;
	}
	std::ofstream output(outputFileName.value());
	if (!output.is_open())
	{
		throw std::invalid_argument("Failed to open file for writing");
	}
	WriteMatrix(output, outField);
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args.has_value())
	{
		return 1;
	}

	try
	{
		Field field = ReadField(args->inputFileName);
		Field result = GenerateNextGeneration(field);
		WriteResult(args->outputFileName, result);
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
