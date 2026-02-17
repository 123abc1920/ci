// 9 номер
#include <iostream>

int main()
{
    int row;
    int col;

    std::cin >> row;
    std::cin >> col;

    int numbers[row][col];

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            numbers[i][j] = 1 + rand() % 20;
        }
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            std::cout << numbers[i][j] << " ";
        }
        std::cout << std::endl;
    }

    int sums[col];
    for (int i = 0; i < col; i++)
    {
        sums[i] = 0;
    }

    for (int j = 0; j < col; j++)
    {
        for (int i = 0; i < row; i++)
        {
            sums[j] += numbers[i][j];
        }
    }

    for (int i = 0; i < col; i++)
    {
        std::cout << sums[i] << " ";
    }

    return 0;
}