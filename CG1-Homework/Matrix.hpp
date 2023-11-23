
#ifndef Matrix_HPP
#define Matrix_HPP

#include <vector>
#include <initializer_list>
#include <cmath>
#include <stdexcept>


class Matrix
{
private:
	const size_t rows;
	const size_t cols;
	std::vector<std::vector<double>> elems;

	public: 
		// Constructors
		Matrix(size_t rows, size_t cols);
		Matrix(std::initializer_list<std::initializer_list<double>> lis);

		// Destructors
		//~Matrix();

		// Gets
		size_t GetRows() const;
		size_t GetCols() const;
		double &Get(size_t r, size_t c);
		const double &Get(size_t r, size_t c) const;

		// Overload +, - and * operators(friends). 
		Matrix operator+ (const Matrix &other) const;
		void operator+ (double scalar);

		Matrix operator- (const Matrix &other) const;
		void operator- (double scalar);

		Matrix operator* (const Matrix &other) const;
		std::vector<double> operator* (const std::vector<double> &other) const;
		void operator* (double scalar);
		
		Matrix Translation(const std::vector<double> &offset);
		Matrix RotationX(double theta);
		Matrix RotationY(double theta);
		Matrix RotationZ(double theta);
		Matrix Scaling(const std::vector<double> &scale);


};

#endif