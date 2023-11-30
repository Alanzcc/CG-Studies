
#ifndef Mat4_HPP
#define Mat4_HPP

#include <vector>
#include <initializer_list>
#include <cmath>
#include <stdexcept>


class Mat4
{
private:
	const size_t rows;
	const size_t cols;
	std::vector<std::vector<double>> elems;

	public: 
		// Constructors
		Mat4(size_t rows, size_t cols);
		Mat4(std::initializer_list<std::initializer_list<double>> lis);

		// Destructors
		//~Mat4();

		// Gets
		size_t GetRows() const;
		size_t GetCols() const;
		double &Get(size_t r, size_t c);
		const double &Get(size_t r, size_t c) const;

		// Overload +, - and * operators(friends). 
		Mat4 operator+ (const Mat4 &other) const;
		void operator+ (double scalar);

		Mat4 operator- (const Mat4 &other) const;
		void operator- (double scalar);

		Mat4 operator* (const Mat4 &other) const;
		std::vector<double> operator* (const std::vector<double> &other) const;
		void operator* (double scalar);
		
		Mat4 Translation(const std::vector<double> &offset);
		Mat4 RotationX(double theta);
		Mat4 RotationY(double theta);
		Mat4 RotationZ(double theta);
		Mat4 Scaling(const std::vector<double> &scale);


};

#endif