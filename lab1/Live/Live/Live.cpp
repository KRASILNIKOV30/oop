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

bool IsInputOpen(ifstream& input)
{

	if (!input.is_open())
	{
		cout << "Failed to open file for reading\n";
		return false;
	}
	
	return true;
}

bool SaveErrorHandling(ostream& output)
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
		cout << "Usage: live.exe <input file> <output file>\n";
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

void GenerateNextGeneration(char inMatrix[MAX_FIELD_SIZE][MAX_FIELD_SIZE], char outMatrix[MAX_FIELD_SIZE][MAX_FIELD_SIZE], size_t fieldWidth, size_t fieldHeight)
{
	int neighboursNumber;
	for (int x = 0; x < fieldHeight; x++)
	{
		for (int y = 0; y < fieldWidth; y++)
		{
			if (inMatrix[x][y] == BOUND)
			{
				outMatrix[x][y] = BOUND;
			}
			else
			{
				neighboursNumber = GetCellNeighboursNumber(inMatrix, { x, y });
				if (inMatrix[x][y] == LIVE_CELL)
				{
					if (neighboursNumber == 2 || neighboursNumber == 3)
					{
						outMatrix[x][y] = LIVE_CELL;
					}
					else
					{
						outMatrix[x][y] = DEAD_CELL;
					}
				}
				else
				{
					if (neighboursNumber == 3)
					{
						outMatrix[x][y] = LIVE_CELL;
					}
					else
					{
						outMatrix[x][y] = DEAD_CELL;
					}
				}
			}
		}
		
	}
}

void ReadMatrix(ifstream& input, char matrix[MAX_FIELD_SIZE][MAX_FIELD_SIZE], size_t& fieldWidth, size_t& fieldHeight)
{
	string str;
	int i = 0;
	while (getline(input, str))
	{
		if (str[0] != BOUND)
		{
			break;
		}
		fieldWidth = str.length() < MAX_FIELD_SIZE ? str.length() : MAX_FIELD_SIZE;
		for (int j = 0; j < str.length() && j < MAX_FIELD_SIZE; j++)
		{
			matrix[i][j] = str[j];
		}
		i++;
		if (i == MAX_FIELD_SIZE)
		{
			fieldHeight = MAX_FIELD_SIZE;
			return;
		}
	}
	fieldHeight = i;
}

bool IsRightBoundAchieved(char currentChar, int x, int y)
{
	return currentChar == BOUND && x != 0 && y != 0;
}

void WriteMatrix(ostream& output, const char matrix[MAX_FIELD_SIZE][MAX_FIELD_SIZE], const size_t fieldWidth, const size_t fieldHeight)
{
	for (int i = 0; i < fieldHeight; i++)
	{
		for (int j = 0; j < fieldWidth; j++)
		{
			output << matrix[i][j];
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
	size_t fieldWidth = 0;
	size_t fieldHeight = 0;

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
