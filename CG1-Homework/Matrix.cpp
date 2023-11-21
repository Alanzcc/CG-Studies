#include "Matrix.hpp"

Matrix::Matrix(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
    //std::vector<std::vector<double>> matrix(this->lines, std::vector<double>(this->columns));
    //this->matrix = matrix;
}


Matrix Matrix::Multiplication(Matrix matrixA, Matrix matrixB)
{
    Matrix matrixC(matrixA.lines, matrixB.columns);
    for(int i = 0; i < matrixA.rows; i++)
    {
        for(int j = 0; j < matrixB.columns; j++)
        {
            for(int k = 0; k < matrixA.columns; k++)
            {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    return matrixC;
}

Matrix::Scaling(double x, double y, double z)
{
    
}
