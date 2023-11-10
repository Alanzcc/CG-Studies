#include "Matrix.hpp"

Matrix::Matrix(int lines, int columns)
{
    this->lines = lines;
    this->columns = columns;
    std::vector<std::vector<double>> matrix(this->lines, std::vector<double>(this->columns));
    this->matrix = matrix;
}