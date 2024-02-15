#include <iostream>
#include <fstream>
#include <vector>
#include <optional>
#include <string>

namespace {
	const char LIVE_CELL = '#';
	const char BOUND = '*';
	const char DEAD_CELL = ' ';
	const int MAX_FIELD_SIZE = 20;
	struct Coordinates {
		int x;
		int y;
	}; 

	struct Field
	{
		char matrix[MAX_FIELD_SIZE][MAX_FIELD_SIZE];
		size_t width;
		size_t height;
	};
}

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3 && argc != 2)
	{
		return std::nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	if (argc == 3) {
		args.outputFileName = argv[2];
	}

	return args;
}

bool IsInputOpen(std::ifstream& input)
{

	if (!input.is_open())
	{
		std::cout << "Failed to open file for reading" << std::endl;
		return false;
	}
	
	return true;
}

bool SaveErrorHandling(std::ostream& output)
{
	if (!output.flush())
	{
		std::cout << "Failed to save data on disk" << std::endl;
		return false;
	}
	return true;
}

bool ProcessArgError(const std::optional<Args>& args)
{
	if (!args.has_value())
	{
		std::cout << "Invalid arguments count" << std::endl;
		std::cout << "Usage: live.exe <input file> <output file>" << std::endl;
		return false;
	}
	return true;
}

int GetCellNeighboursNumber(char const matrix[MAX_FIELD_SIZE][MAX_FIELD_SIZE], Coordinates coords)
{
	int result = 0;
	for (int x = coords.x - 1; x <= coords.x + 1; x++)
	{
		for (int y = coords.y - 1; y <= coords.y + 1; y++)
		{
			if (!(x == coords.x && y == coords.y) && matrix[x][y] == LIVE_CELL)
			{
				result++;
			}
		}
	}

	return result;
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

void GenerateNextGeneration(Field const& inField, Field& outField)
{
	outField.width = inField.width;
	outField.height = inField.height;
	for (int x = 0; x < inField.height; x++)
	{
		for (int y = 0; y < inField.width; y++)
		{
			
			int neighboursNumber = GetCellNeighboursNumber(inField.matrix, { x, y });
			switch (inField.matrix[x][y])
			{
				case BOUND:
					outField.matrix[x][y] = BOUND;
					break;
				case LIVE_CELL:
					outField.matrix[x][y] = GetLiveCellNextState(neighboursNumber);
					break;
				case DEAD_CELL:
					outField.matrix[x][y] = GetDeadCellNextState(neighboursNumber);
					break;
				default:
					outField.matrix[x][y] = DEAD_CELL;
					break;
			}
		}	
	}
}

int GetFieldWidth(size_t rowLength)
{
	if (rowLength < MAX_FIELD_SIZE)
	{
		return rowLength;
	}
	return MAX_FIELD_SIZE;
}

//поменять x y (Исправлено)
void ReadMatrix(std::istream& input, Field& field)
{
	std::string str;
	Coordinates coords = { 0, 0 };
	while (std::getline(input, str))
	{
		if (str[0] != BOUND)
		{
			break;
		}
		field.width = GetFieldWidth(str.length());
		for (coords.y = 0; coords.y < str.length() && coords.y < MAX_FIELD_SIZE; coords.y++)
		{
			field.matrix[coords.x][coords.y] = str[coords.y];
		}
		coords.x++;
		if (coords.x == MAX_FIELD_SIZE)
		{
			field.height = MAX_FIELD_SIZE;
			return;
		}
	}
	field.height = coords.x;
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
}

bool WriteResult(std::string outputFileName, Field const& outField)
{
	if (outputFileName == "")
	{
		WriteMatrix(std::cout, outField);
	}
	else
	{
		std::ofstream output(outputFileName);
		WriteMatrix(output, outField);
		if (!SaveErrorHandling(output))
		{
			return false;
		}
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
	
	/*if (!IsInputOpen(input))
	{
		return 1;
	}*/

	Field inField;
	Field outField;

	ReadMatrix(input, inField);
	GenerateNextGeneration(inField, outField);

	if (!WriteResult(args->outputFileName, outField))
	{
		return 1;
	}

	return 0;
}
