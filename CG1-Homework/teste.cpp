#include "Matrix2D.hpp"
using namespace std;

class Matrix
{
    
    public:
        int lines, columns;
        vector<vector<double>> matrix; 
        
        Matrix(int lines, int columns) {

            vector<vector<double>> matrix(lines, vector<double>(columns));
            this->matrix = matrix;

            //print matrix
            for(int i = 0; i<lines; i++)
            {
                for(int j = 0; j<columns; j++)
                {
                    cout << matrix[i][j] << " ";
                }
                cout << endl;
            }
        };
};

int main()
{
    Matrix Matriz(5, 12);
    for(int i = 0; i<lines; i++)
        {
            for(int j = 0; j<columns; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    return 0;
}