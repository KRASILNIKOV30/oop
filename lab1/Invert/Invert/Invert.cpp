#include <iostream>
#include <optional>
#include <fstream>
#include <iomanip>
#include <array>

constexpr double EPSILON = 1e-3;
constexpr int PRECISION = 3;

using Mat3x3 = std::array<std::array<double, 3>, 3>;

struct Args
{
    std::string inputMatrixFile;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid arguments count" << std::endl;
        std::cout << "Usage: invert.exe <input matrix file>" << std::endl;
        return std::nullopt;
    };
    Args args;
    args.inputMatrixFile = argv[1];
    return args;
}

// Вернуть матрицу или выбросить исключение (Исправлено)
Mat3x3 ReadMatrix(std::string const& inputFileName)
{
    std::ifstream input(inputFileName);
    if (!input.is_open())
    {
        throw std::invalid_argument("Failed to open file for reading");
    }

    Mat3x3 matrix;
    // Считывать в элемент массива (Исправлено)
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!(input >> matrix[i][j]))
            {
                throw std::runtime_error("Error while reading input file");
            }
        }
    }
    return matrix;
}

void WriteMatrix(std::ostream& output, Mat3x3 const& matrix)
{
    // использовать setw и fixed (Исправлено)
    std::cout << std::setprecision(PRECISION) << std::fixed;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            double el = matrix[i][j];
            output << std::setw(PRECISION * 2) << ((std::abs(el) < EPSILON) ? 0 : el) << " ";
        }
        output << std::endl;
    }
}

double GetDeterminant(Mat3x3 const& matrix)
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

double GetMinorDeterminant(int i, int j, Mat3x3 const& matrix)
{
    int i1 = i == 0 ? 1 : 0;
    int i2 = i == 2 ? 1 : 2;
    int j1 = j == 0 ? 1 : 0;
    int j2 = j == 2 ? 1 : 2;

    return matrix[i1][j1] * matrix[i2][j2] - matrix[i1][j2] * matrix[i2][j1];
}

// Возвращать optional<Mat3x3> (Исправлено)
std::optional<Mat3x3> InvertMatrix(Mat3x3 const& matrix)
{
    double det = GetDeterminant(matrix);

    if (std::abs(det) < EPSILON)
    {
        // Убрать вывод (Исправлено)
        return std::nullopt;
    }

    Mat3x3 result;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result[i][j] = GetMinorDeterminant(j, i, matrix) / det;
            result[i][j] *= ((i + j) % 2) ? -1 : 1;
        }
    }

    return result;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);

    if (!args.has_value())
    {
        return 1;
    }

    // Вывод в std::cout (Исправлено)
    // принимать имя файла (Исправлено)
    Mat3x3 matrix;
    try
    {
        matrix = ReadMatrix(args->inputMatrixFile);
        auto invertedMatrix = InvertMatrix(matrix);
        if (!invertedMatrix.has_value())
        {
            std::cout << "Inverted matrix does not exist" << std::endl;
            return 1;
        }

        WriteMatrix(std::cout, invertedMatrix.value());
    }
    catch (std::exception const& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}