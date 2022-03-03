#include <iostream>
#include <optional>
#include <fstream>

struct Args
{
    std::string inputMatrixFile1;
    std::string inputMatrixFile2;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        //1. Вывод ошибок раскиданм по программе, лучше его объеденить
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: multmatrix.exe <matrix file1> <matrix file2>\n";
        return std::nullopt;
    };
    Args args;
    args.inputMatrixFile1 = argv[1];
    args.inputMatrixFile2 = argv[2];
    return args;
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

void WriteMatrix(double matrix[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout.precision(3);
            std::cout << matrix[i][j];
            std::cout << " ";
        };
        std::cout << std::endl;
    }
}

void MultiplyMatrix(double matrix1[3][3], double matrix2[3][3], double resultMatrix[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            resultMatrix[i][j] = matrix1[i][0] * matrix2[0][j] + matrix1[i][1] * matrix2[1][j] + matrix1[i][2] * matrix2[2][j];
        }
    }
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return 1;
    };

    //3. Часть кода можно разнести по различным функциям
    //4. можно проверить еще один кейс, когда не передано ни одного параметра
    std::ifstream matrixFile1(args->inputMatrixFile1);
    std::ifstream matrixFile2(args->inputMatrixFile2);

    //2. Можно разделить на две проверки для более точной информации для пользователя
    if (!matrixFile1.is_open() || !matrixFile2.is_open())
    {
        std::cout << "Failed to open file for reading\n";
        return 1;
    }

    double matrix1[3][3];
    double matrix2[3][3];

    if (!ReadMatrix(matrixFile1, matrix1) || !ReadMatrix(matrixFile2, matrix2))
    {
        return 1;
    }

    double resultMatrix[3][3];

    MultiplyMatrix(matrix1, matrix2, resultMatrix);

    WriteMatrix(resultMatrix);   
}