#include <iostream>
#include <optional>
#include <fstream>
#include <iomanip>

constexpr double EPSILON = 1e-7;
constexpr int PRECISION = 3;

struct Args
{
    std::string inputMatrixFile;
    std::string outputMatrixFile;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: invert.exe <input matrix file> <output matrix file>\n";
        return std::nullopt;
    };
    Args args;
    args.inputMatrixFile = argv[1];
    args.outputMatrixFile = argv[2];
    return args;
}

bool OpenStreamsErrorHandling(std::ifstream& input, std::ofstream& output)
{

    if (!input.is_open())
    {
        std::cout << "Failed to open file for reading\n";
        return false;
    }
    if (!output.is_open())
    {
        std::cout << "Failed to open file for writing\n";
        return false;
    }
    return true;
}

bool ReadMatrix(std::istream& input, double matrix[3][3])
{
    double inValue;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (input >> inValue)
            {
                matrix[i][j] = inValue;
            }
            else
            {
                std::cout << "Invalid input matrix\n";
                return false;
            }
        }
    }
    return true;
}

double SetPrecision(double i, int p)
{
    double coef = std::pow(10, p);
    double result = std::round(i * coef) / coef;
    return result == -0 ? 0 : result;
}

void WriteMatrix(std::ostream& output, double matrix[3][3])
{
    output << std::setprecision(PRECISION);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            output << SetPrecision(matrix[i][j], PRECISION) << " ";
        }
        output << std::endl;
    }
}

double GetDeterminant(const double matrix[3][3])
{
    double positiveTriangle1 = matrix[0][1] * matrix[1][2] * matrix[2][0];
    double positiveTriangle2 = matrix[1][0] * matrix[2][1] * matrix[0][2];
    double positiveDiagonal = matrix[0][0] * matrix[1][1] * matrix[2][2];
    
    double negativeTriangle1 = matrix[0][1] * matrix[1][0] * matrix[2][2];
    double negativeTriangle2 = matrix[0][0] * matrix[1][2] * matrix[2][1];
    double negativeDiagonal = matrix[0][2] * matrix[1][1] * matrix[2][0];

    return positiveTriangle1 + positiveTriangle2 + positiveDiagonal
        - negativeTriangle1 - negativeTriangle2 - negativeDiagonal;
}

double GetMinorDeterminant(int i, int j, double matrix[3][3])
{
    int i1 = i == 0 ? 1 : 0;
    int i2 = i == 2 ? 1 : 2;
    int j1 = j == 0 ? 1 : 0;
    int j2 = j == 2 ? 1 : 2;

    return matrix[i1][j1] * matrix[i2][j2] - matrix[i1][j2] * matrix[i2][j1];
}

bool InvertMatrix(double matrix[3][3], double invertMatrix[3][3])
{
    double det = GetDeterminant(matrix);

    if (std::abs(det) < EPSILON)
    {
        std::cout << "Determinant is equal to zero" << std::endl;
        return false;
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            invertMatrix[i][j] = GetMinorDeterminant(j, i, matrix) / det;
            invertMatrix[i][j] *= ((i + j) % 2) ? -1 : 1;
        }
    }

    return true;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);

    if (!args.has_value())
    {
        return 1;
    }

    std::ifstream inMatrixStream(args->inputMatrixFile);
    std::ofstream outMatrixStream(args->outputMatrixFile);

    if (!OpenStreamsErrorHandling(inMatrixStream, outMatrixStream))
    {
        return 1;
    }

    double matrix[3][3];
    if (!ReadMatrix(inMatrixStream, matrix))
    {
        return 1;
    }

    double resultMatrix[3][3];

    if (!InvertMatrix(matrix, resultMatrix))
    {
        return 1;
    }

    WriteMatrix(outMatrixStream, resultMatrix);
}