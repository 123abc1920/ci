// 9 номер
#include <iostream>

void printArray(int **arr, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            std::cout << *(*(arr + i) + j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void countSums(int **arr, int *sums, int row, int col)
{
    for (int j = 0; j < col; j++)
    {
        for (int i = 0; i < row; i++)
        {
            *(sums + j) += *(*(arr + i) + j);
        }
    }
}

int getNumber()
{
    return 1 + rand() % 20;
}

int main()
{
    int row;
    int col;

    std::cout << "Размеры матрицы:" << std::endl;
    std::cin >> row;
    std::cin >> col;
    std::cout << std::endl;

    int **numbers = new int *[row];
    for (int i = 0; i < row; i++)
    {
        *(numbers + i) = new int[col];
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            *(*(numbers + i) + j) = getNumber();
        }
    }

    std::cout << "Матрица:" << std::endl;
    printArray(numbers, row, col);

    int *sums = new int[col];
    for (int i = 0; i < col; i++)
    {
        *(sums + i) = 0;
    }

    countSums(numbers, sums, row, col);

    std::cout << "Вектор:" << std::endl;
    for (int i = 0; i < col; i++)
    {
        std::cout << *(sums + i) << " ";
    }
    std::cout << std::endl;

    delete[] sums;

    for (int i = 0; i < row; i++)
    {
        delete[] *(numbers + i);
    }
    delete[] numbers;

    return 0;
}