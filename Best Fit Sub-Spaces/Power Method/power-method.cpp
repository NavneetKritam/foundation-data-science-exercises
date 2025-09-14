#include <vector>
#include <cstdio>
#include <random>
#include <cmath>
#include <string>
#include <ctime>
#include <algorithm>
#include "power-method.h"

// TODO: Add size sanity checks to all functions

int main(){
    /*
        Upper Diagonal Vector of form [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
                                       [2, 3, 4, 5, 6, 7, 8, 9, 10, 0]
                                       ....
                                       [10, 0, 0, 0, 0, 0, 0, 0, 0, 0]]

    */
    std::vector<std::vector<double>> upper_diagonal = create_upper_diagonal_matrix();
    printf("Problem Matrix: \n");
    display_matrix(upper_diagonal); // Display the matrix
    clock_t start_time = clock();
    printf("\n-----------------\n\nv1 by power method:\n-------------------\n\n");
    display_vector(power_method_v1(upper_diagonal));
    printf("\nTime to run power method for v1: %lf\n", (double)(clock() - start_time)/CLOCKS_PER_SEC);
    printf("\n-----------------\n\n4 Singular Vectors by power method:\n-------------------\n\n");
    start_time = clock();
    display_matrix(power_method(upper_diagonal, 4));
    printf("\nTime to run power method 4 singular vectors: %lf\n", (double)(clock() - start_time)/CLOCKS_PER_SEC);
    return 0;
}

/*
    Upper Diagonal Vector of form [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
                                    [2, 3, 4, 5, 6, 7, 8, 9, 10, 0]
                                    ....
                                    [10, 0, 0, 0, 0, 0, 0, 0, 0, 0]]

*/
std::vector<std::vector<double>> create_upper_diagonal_matrix()
{
    std::vector<std::vector<double>> upper_diagonal(10, std::vector<double>(10, 0.0));
    int i, j;
    for (i = 0; i < 10; i++)
        for (j = 0; j < 10 - i; j++)
            upper_diagonal.at(i).at(j) = i + j + 1;
    return upper_diagonal;
}

// Display the matrix
template<typename T>
void display_matrix(const std::vector<std::vector<T>> &matrix)
{
    int i;
    for (i = 0; i < matrix.size(); i++)
    {
        display_vector(matrix.at(i));
    }
}

// Display vector
template<typename T>
void display_vector(const std::vector<T> &vec){
    int j;
    for(j = 0; j < vec.size(); j++)
        printf("%s ", (std::to_string(vec.at(j))).c_str());
    printf("\n");
}

// Generate 1-D gaussian with variance, v and mean, m
std::vector<double> generate_gaussian_vector(std::vector<double> m, double v){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<double> result(m.size());
    std::normal_distribution<double> nd{0.0, v};
    int i;
    for(i = 0; i < m.size(); i++)
        result.at(i) = nd(gen) + m.at(i);
    return result;
}

template<typename T>
std::vector<T>& vector_matrix_mul_inplace(const std::vector<std::vector<T>> &matrix, std::vector<T> &vec){
    int n_col = matrix.at(0).size(), n_row = matrix.size();
    T result;
    //TODO: check dimenstion for determining legality of operation
    //do matrix mul
    int i, j;
    for(j = 0; j != n_col; ++j){
        result = (T)0;
        for(i = 0; i != n_row; ++i)
            if(!(matrix.at(i).at(j) == (T)0 || vec.at(j) == (T)0))
                result += matrix.at(i).at(j) * vec.at(j);
        vec.at(j) = result;
    }   
    return vec;
}

// Normalize given vector
std::vector<double>& normalize_vector_inplace(std::vector<double> &vec){
    double norm = get_norm(vec);;
    int i;
    if(norm == 0.0)
        return vec;
    for(i = 0; i < vec.size(); i++)
        vec.at(i) = vec.at(i) / norm;
    return vec;
}

// Subtract vector second from first and save the result in first
template<typename T>
std::vector<T>& subtract_vectors_inplace(std::vector<T> &first, const std::vector<T> &second, T second_vec_multiple){
    int i;
    for(i = 0; i != first.size(); ++i)
        first.at(i) -= second_vec_multiple * ((i < second.size()) ? second.at(i) : (T)0);
    return first;
}

template<typename T>
T dot_product(const std::vector<T> &first, const std::vector<T> &second){
    T result = (T) 0;
    int i;
    for(i = 0; i < first.size(); ++i)
        result += first.at(i) * ((i < second.size()) ? second.at(i) : (T)0);
    return result;
}

double get_norm(const std::vector<double> &vec)
{
    double norm = 0.0;
    int i;
    for (i = 0; i < vec.size(); i++)
        norm += pow(vec.at(i), 2);
    norm = pow(norm, 0.5);
    return norm;
}

// Transpose the matrix
template<typename T>
std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>> &matrix){
    if(matrix.empty() || matrix.at(0).empty())
        return matrix;
    // TODO: To check if all vectors are of same size in each row
    int n_col = matrix.at(0).size(), n_row = matrix.size();
    std::vector<std::vector<T>> transposed_matrix(n_col, std::vector<T>(n_row));
    int i, j;
    for(i = 0; i < n_row; i++)
        for(j = 0; j < n_col; j++)
            transposed_matrix.at(j).at(i) = matrix.at(i).at(j);
    return transposed_matrix;
}

// Power method for v1
std::vector<double> power_method_v1(const std::vector<std::vector<double>> &matrix, const double min_error, const int max_iterations){
    int vector_size = matrix.size();
    std::vector<double> mean(vector_size, 0.0);
    std::vector<double> x = generate_gaussian_vector(mean, 1.0);
    std::vector<std::vector<double>> transposed_matrix = transpose(matrix);
    std::vector<double> previous_x(vector_size);
    int i;
    for(i = 0; i < max_iterations; i++){
       x = normalize_vector_inplace(vector_matrix_mul_inplace(matrix, vector_matrix_mul_inplace(transposed_matrix, x)));
       if(i > 0){
        previous_x = subtract_vectors_inplace(previous_x, x);
        if(get_norm(previous_x) < min_error)
            return x;
       }
       std::copy(x.begin(), x.end(), previous_x.begin());
    }
    return x;
} 

// Power method for first k singular vectors
std::vector<std::vector<double>> power_method(const std::vector<std::vector<double>> &matrix, const int k, const double min_error, const int max_iterations){
    int vector_size = matrix.size();
    int i, j; // iterator int
    // Create first estimation of k-singular vectors, viz, x, Ax, .., A^(k-1)x
    std::vector<std::vector<double>> singular_vectors;
    std::vector<double> mean(vector_size, 0.0);
    // Generate k random vectors
    for(i = 0; i != k; ++i)
        singular_vectors.push_back(generate_gaussian_vector(mean, 1.0));
    // Calculate in place basis formed by k-vectors
    singular_vectors = calculate_basis_inplace(singular_vectors);
    //  Deep Copy of vector of vectors for comparison
    std::vector<std::vector<double>> previous_singular_vectors(k, std::vector<double>(vector_size));
    previous_singular_vectors = deep_copy_2D(singular_vectors, previous_singular_vectors);
    // Iterate through i for max_iterations, applying A to singular vectors and calculating its basis
    double epsilon; // Change in vector in total norm
    for(i = 0; i != max_iterations; i++){
        epsilon  = 0.0;
        // Calculating A times previous singular vectors
        for(j = 0; j < k; j++)
            singular_vectors.at(j) = vector_matrix_mul_inplace(matrix, singular_vectors.at(j));
        singular_vectors = calculate_basis_inplace(singular_vectors); // Calculate the basis ie new singular vectors
        // Calculate total norm of the difference
        for(j = 0; j < k; j++)
            epsilon += get_norm(subtract_vectors_inplace(previous_singular_vectors.at(j), singular_vectors.at(j)));
        if(epsilon < min_error)
            return singular_vectors;
        previous_singular_vectors = deep_copy_2D(singular_vectors, previous_singular_vectors); // saving this for next iteration

    }
    return singular_vectors;
}

// Calculate orthonormal basis in place(replacing) for spanning vectors
std::vector<std::vector<double>>& calculate_basis_inplace(std::vector<std::vector<double>> &spanning_vectors){
    int i, j; // iterating ints
    int n = spanning_vectors.size(); // number of spanning vectors
    for(i = 0; i != n; ++i){
        spanning_vectors.at(i) = normalize_vector_inplace(spanning_vectors.at(i));
        for(j = i + 1; j < n; ++j){
            spanning_vectors.at(j) = subtract_vectors_inplace(spanning_vectors.at(j), spanning_vectors.at(i), dot_product(spanning_vectors.at(j), spanning_vectors.at(i))); // Subtracting projection of vi-1 from vi
        }
    }
    return spanning_vectors;
}

// Deep Copy source to destination 2D vectors
template<typename T>
std::vector<std::vector<T>>& deep_copy_2D(const std::vector<std::vector<T>> &source, std::vector<std::vector<T>> &destination){
    int i;
    for(i = 0; i < source.size(); i++)
        std::copy(source.at(i).begin(), source.at(i).end(), destination.at(i).begin());
    return destination;
}