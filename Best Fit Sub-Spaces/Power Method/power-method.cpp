#include <vector>
#include <iostream>
#include "power-method.h"

using namespace std;

int main(){
    /*
        Upper Diagonal Vector of form [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
                                       [2, 3, 4, 5, 6, 7, 8, 9, 10, 0]
                                       ....
                                       [10, 0, 0, 0, 0, 0, 0, 0, 0, 0]]

    */
    vector<vector<int>> upper_diagonal(10, vector<int>(10, 0)); 
    int i, j;
    for(i = 0; i < 10; i++)
        for(j = 0; j < 10 - i; j++)
            upper_diagonal[i][j] = i + j + 1;
    display_matrix(i, j, upper_diagonal);
    return 0;
}

void display_matrix(int &i, int &j, std::vector<std::vector<int>> &upper_diagonal)
{
    // Display the matrix
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
            cout << upper_diagonal[i][j] << " ";
        cout << endl;
    }
}
