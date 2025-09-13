#include <vector>
#include <iostream>
#include <random>
#include "power-method.h"


int main(){
    /*
        Upper Diagonal Vector of form [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
                                       [2, 3, 4, 5, 6, 7, 8, 9, 10, 0]
                                       ....
                                       [10, 0, 0, 0, 0, 0, 0, 0, 0, 0]]

    */
    std::vector<std::vector<int>> upper_diagonal = create_upper_diagonal_matrix();
    std::cout << "Problem Matrix: " << std::endl;
    display_matrix(upper_diagonal); // Display the matrix
    // Get a Gaussian 1-D spherical vector with mean 0 of size 10 and variance 1 called x
    int vector_size = 10;
    std::vector<float> mean(vector_size, 0.0);
    std::vector<float> x = generate_gaussian_vector(mean, 1.0);
    std::cout << "Gaussian Vector of size 10: " << std::endl;
    display_vector(x); // Display random vector
    return 0;
}

/*
    Upper Diagonal Vector of form [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
                                    [2, 3, 4, 5, 6, 7, 8, 9, 10, 0]
                                    ....
                                    [10, 0, 0, 0, 0, 0, 0, 0, 0, 0]]

*/
std::vector<std::vector<int>> create_upper_diagonal_matrix()
{
    std::vector<std::vector<int>> upper_diagonal(10, std::vector<int>(10, 0));
    int i, j;
    for (i = 0; i < 10; i++)
        for (j = 0; j < 10 - i; j++)
            upper_diagonal[i][j] = i + j + 1;
    return upper_diagonal;
}

// Display the matrix
template<typename T>
void display_matrix(const std::vector<std::vector<T>> &matrix)
{
    int i;
    for (i = 0; i < matrix.size(); i++)
    {
        display_vector(matrix[i]);
    }
}

// Display vector
template<typename T>
void display_vector(const std::vector<T> &vec){
    int j;
    for(j = 0; j < vec.size(); j++)
        std::cout << vec[j] << " ";
    std::cout << std::endl;
}

// Generate 1-D gaussian with variance, v and mean, m
std::vector<float> generate_gaussian_vector(std::vector<float> m, float v){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<float> result(m.size());
    std::normal_distribution<float> nd{0.0, v};
    int i;
    for(i = 0; i < m.size(); i++)
        result[i] = nd(gen) + m[i];
    return result;
}
