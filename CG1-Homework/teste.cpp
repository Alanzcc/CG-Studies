#include <iostream>
#include <vector>
#include <cmath>
#include <initializer_list>
#include "vec3Math.hpp"

int main()
{
    std::vector<double> A = {1, 2, 3};
    std::initializer_list<std::initializer_list<double>> B = 
                            {{0, 0, 1},
                             {0, 1, 0},
                             {1, 0, 0}};
    std::initializer_list<std::initializer_list<double>> C = B;
    printf("%f", C[0][0]);

    std::cout << A[0] << " "<< A[1] << " " << A[2] << " " << std::endl;
    return 0;
    
}
