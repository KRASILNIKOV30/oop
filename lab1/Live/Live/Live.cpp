#include <iostream>
#include <fstream>
#include <vector>
#include <optional>
#include <string>

using namespace std;

namespace {
	const char LIVE_CELL = '#';
	const char BOUND = '*';
	const char DEAD_CELL = ' ';
	const int MAX_FIELD_SIZE = 20;
	struct Coordinates {
		int x;
		int y;
	};
}

struct Args
{
	string inputFileName;
	string outputFileName;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3 && argc != 2)
	{
		return nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	if (argc == 3) {
		args.outputFileName = argv[2];
	}

	return args;
}

//поменять название: не ожидпется вывод
bool IsInputOpen(ifstream& input)
{

	if (!input.is_open())
	{
		cout << "Failed to open file for reading" << endl;
		return false;
	}
	
	return true;
}

bool SaveErrorHandling(ostream& output)
{
	if (!output.flush())
	{
		cout << "Failed to save data on disk" << endl;
		return false;
	}
	return true;
}

bool ProcessArgError(const optional<Args>& args)
{
	if (!args.has_value())
	{
		cout << "Invalid arguments count" << endl;
		cout << "Usage: live.exe <input file> <output file>" << endl;
		return false;
	}
	return true;
}

int GetCellNeighboursNumber(char matrix[MAX_FIELD_SIZE][MAX_FIELD_SIZE], Coordinates coords)
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

#if 0
Generation GenerateNext(const Generation& generation)
{

}
#endif

void GenerateNextGeneration(char inMatrix[MAX_FIELD_SIZE][MAX_FIELD_SIZE], char outMatrix[MAX_FIELD_SIZE][MAX_FIELD_SIZE], size_t fieldWidth, size_t fieldHeight)
{
	for (int x = 0; x < fieldHeight; x++)
	{
		for (int y = 0; y < fieldWidth; y++)
		{
			
			int neighboursNumber = GetCellNeighboursNumber(inMatrix, { x, y });
			switch (inMatrix[x][y])
			{
				case BOUND:
					outMatrix[x][y] = BOUND;
					break;
				case LIVE_CELL:
					outMatrix[x][y] = GetLiveCellNextState(neighboursNumber);
					break;
				case DEAD_CELL:
					outMatrix[x][y] = GetDeadCellNextState(neighboursNumber);
					break;
				default:
					outMatrix[x][y] = DEAD_CELL;
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

//можно не выделять в функцию
bool NoFieldInRow(char firstRowElement)
{
	return firstRowElement != BOUND;
}

//поменять x y
void ReadMatrix(ifstream& input, char matrix[MAX_FIELD_SIZE][MAX_FIELD_SIZE], int& fieldWidth, int& fieldHeight)
{
	string str;
	Coordinates coords = { 0, 0 };
	while (getline(input, str))
	{
		if (NoFieldInRow(str[0]))
		{
			break;
		}
		fieldWidth = GetFieldWidth(str.length());
		for (coords.y = 0; coords.y < str.length() && coords.y < MAX_FIELD_SIZE; coords.y++)
		{
			matrix[coords.x][coords.y] = str[coords.y];
		}
		coords.x++;
		if (coords.x == MAX_FIELD_SIZE)
		{
			fieldHeight = MAX_FIELD_SIZE;
			return;
		}
	}
	fieldHeight = coords.x;
}

void WriteMatrix(ostream& output, const char matrix[MAX_FIELD_SIZE][MAX_FIELD_SIZE], int fieldWidth, int fieldHeight)
{
	Coordinates coords = { 0, 0 };
	for (coords.x; coords.x < fieldHeight; coords.x++)
	{
		for (coords.y = 0; coords.y < fieldWidth; coords.y++)
		{
			output << matrix[coords.x][coords.y];
		}
		output << endl;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!ProcessArgError(args))
	{
		return 1;
	}

	ifstream input(args->inputFileName, ios::in);
	
	if (!IsInputOpen(input))
	{
		return 1;
	}

	char inMatrix[MAX_FIELD_SIZE][MAX_FIELD_SIZE];
	char outMatrix[MAX_FIELD_SIZE][MAX_FIELD_SIZE];
	int fieldWidth = 0;
	int fieldHeight = 0;

	ReadMatrix(input, inMatrix, fieldWidth, fieldHeight);
	GenerateNextGeneration(inMatrix, outMatrix, fieldWidth, fieldHeight);

	if (args->outputFileName == "")
	{
		WriteMatrix(cout, outMatrix, fieldWidth, fieldHeight);
	}
	else
	{
		ofstream output(args->outputFileName, ios::out);
		WriteMatrix(output, outMatrix, fieldWidth, fieldHeight);
		if (!SaveErrorHandling(output))
		{
			return 1;
		}
	}

	return 0;
}
