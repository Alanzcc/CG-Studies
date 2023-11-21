#include <iostream>
#include <vector>
#include "vec3Math.hpp"

int main()
{
    std::vector<double> center = {0, 0, -700};
    std::vector<double> normal = {0, 0, 1};
    
    double N5 = dotProduct(minusVectors(A, B), A);
    double N6 = dotProduct(multiplyByScalar(A, 2), B);
    double N7 = dotProduct(crossProduct(A, B), B);
   
    

    std::cout << N << " "<< N2 << " " << N3 << " " << N4 << std::endl;
    return 0;
    
}
