#ifndef Matrix_HPP
#define Matrix_HPP

#include <vector>

class Matrix
{
    public:
        int lines, columns;
        std::vector<std::vector<double>> matrix;
        Matrix(int lines, int columns);
};

#endif