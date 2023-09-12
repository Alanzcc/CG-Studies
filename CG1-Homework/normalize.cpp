#include <iostream>
#include <cmath>

int main()
{
    float vector[3] = {255, 0, 0};
    float norm = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
    vector[0] = (vector[0] / norm);

    printf("%f\n", vector[0]);
}