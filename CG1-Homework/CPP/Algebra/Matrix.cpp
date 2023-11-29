#include "Matrix.hpp"

Matrix::Matrix(size_t r, size_t c) : rows{r}, cols{c}, elems{ std::vector<std::vector<double>>(rows, std::vector<double>(cols)) } {}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> lis)
	: rows{lis.size()}, cols{lis.begin()->size()}, elems{std::vector<std::vector<double>>(rows, std::vector<double>(cols))}
{
	size_t i = 0 , j = 0;
	for (auto &row : lis) {
		for (double data : row) {
			elems[i][j++] = data;
	}
		++i;
	}
}

size_t Matrix::GetRows() const { return rows; }
size_t Matrix::GetCols() const { return cols; }
double &Matrix::Get(size_t i, size_t j)
{
	if (i > rows || j > cols) 
		throw std::out_of_range("Invalid Matrix range");
	
	return elems[i][j];
}
const double& Matrix::Get(size_t i, size_t j) const {
	if (i > rows || j > cols)
		throw std::out_of_range("Invalid Matrix range!");
	return elems[i][j];
}

Matrix Matrix::Translation(const std::vector<double>& offset)
{
	return { {1, 0, 0, offset[0]},
			 {0, 1, 0, offset[1]},
			 {0, 0, 1, offset[2]},
			 {0, 0, 0, 1} };
}

Matrix Matrix::RotationX (double theta)
{
	return { {1, 0, 0, 0},
			 {0, cos(theta), sin(theta), 0},
			 {0, -sin(theta), cos(theta), 0},
			 {0, 0, 0, 1} };
}

Matrix Matrix::RotationY (double theta)
{
	return { {cos(theta), 0, -sin(theta), 0},
			 {0, 1, 0, 0},
			 {sin(theta), 0, cos(theta), 0},
			 {0, 0, 0, 1} };
}

Matrix Matrix::RotationZ (double theta)
{
	return { {cos(theta), -sin(theta), 0, 0},
			 {sin(theta), cos(theta), 0, 0},
			 {0, 0, 1, 0},
			 {0, 0, 0, 1} };
}


Matrix Matrix::Scaling(const std::vector<double>& scale)
{
	return { {scale[0], 0, 0, 0},
			 {0, scale[1], 0, 0},
			 {0, 0, scale[2], 0},
			 {0, 0, 0,         1} };
}

Matrix Matrix::operator+ (const Matrix& other) const
{
	if (rows != other.GetRows() || cols != other.GetCols())
		throw std::out_of_range("Invalid Matrix range!");
	Matrix sumMat = Matrix(rows, other.GetCols());
	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < other.GetCols(); ++j)
		{
			sumMat.elems[i][j] = elems[i][j] + other.elems[i][j];
		}
	}
	return sumMat;
}
void Matrix::operator+ (double scalar)
{
	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < cols; ++j)
		{
			elems[i][j] += scalar;
		}
	}
}

Matrix Matrix::operator- (const Matrix& other) const
{
	if (rows != other.GetRows() || cols != other.GetCols())
		throw std::out_of_range("Invalid Matrix range!");
	Matrix minusMat = Matrix(rows, other.GetCols());
	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < other.GetCols(); ++j)
		{
			minusMat.elems[i][j] = elems[i][j] + other.elems[i][j];
		}
	}
	return minusMat;
}
void Matrix::operator- (double scalar)
{
	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < cols; ++j)
		{
			elems[i][j] -= scalar;
		}
	}
}

Matrix Matrix::operator* (const Matrix &other) const
{
	if (cols != other.GetRows())
		throw std::out_of_range("Invalid Matrix range!");
	Matrix multMat = Matrix(rows, other.GetCols());
	double sum;
	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < other.GetCols(); ++j)
		{
			sum = 0;
			for (size_t k = 0; k < cols; ++k)
			{
				sum += Get(i, k) * other.Get(k, j);
			}
			multMat.Get(i, j) = sum;
		}
	}
	return multMat;
}
std::vector<double> Matrix::operator* (const std::vector<double> &other) const
{
	if (cols != 4)
		throw std::out_of_range("Invalid Matrix range!");
	std::vector<double> result;
	int k = 0;
	for (size_t i = 0; i < rows; ++i)
	{
	result.push_back(other[0] * Get(i, 0) + other[1] * Get(i, 1) + other[2] * Get(i, 2) + Get(i, 4));
	}
	return result;
}
void Matrix::operator* (double scalar)
{
	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < cols; ++j)
		{
			elems[i][j] *= scalar;
		}
	}
}
