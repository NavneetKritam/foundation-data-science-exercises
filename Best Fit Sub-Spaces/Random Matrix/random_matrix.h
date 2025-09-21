#include "..\Power Method\power-method.h"

// Generate n_row by n_col matrix with entries x~[0, 1]
std::vector<std::vector<double>> construct_random_matrix(const int n_rows, const int n_columns){
    std::vector<std::vector<double>> random_matrix(n_rows, std::vector<double>(n_columns));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> uniform_dist{0.0, 1.0};
    int i, j;
    for(i = 0; i != n_rows; ++i)
        for(j = 0; j != n_columns; ++j)
            random_matrix.at(i).at(j) = uniform_dist(gen);
    return random_matrix;
}

// Calculate frobenius norm
double frobenius_norm(const std::vector<std::vector<double>> &matrix){
    double norm=0.0;
    int i;
    for(i = 0; i != matrix.size(); ++i)
        norm += dot_product(matrix.at(i), matrix.at(i));
    return pow(norm, 0.5);
}

// Get Singular Value given singular vector
double get_singular_val(const std::vector<std::vector<double>> &matrix, const std::vector<double> &sing_vec){
    std::vector<double> temp(sing_vec);
    return get_norm(vector_matrix_mul_inplace(matrix, temp));
}

// Returns u times vT
std::vector<std::vector<double>> u_times_vT(const std::vector<double> &u, const std::vector<double> &v){
    std::vector<std::vector<double>> product(u.size(), std::vector<double>(v.size()));
    int i, j;
    for(i = 0; i != u.size(); ++i)
        for(j = 0; j != v.size(); ++j)
            product.at(i).at(j) = u.at(i) * v.at(j);
    return product; 
}

// Get \sigma * u * vT given singular vector aka matrix component
std::vector<std::vector<double>> get_matrix_component(const std::vector<std::vector<double>> &matrix, const std::vector<double> &v){
    std::vector<double> sigma_times_u(v);
    sigma_times_u = vector_matrix_mul_inplace(matrix, sigma_times_u);
    return u_times_vT(sigma_times_u, v);
}

// Save matrix1 + matrix2 to matrix1 and return it
template<typename T>
std::vector<std::vector<T>>& matrix_addition_inplace(std::vector<std::vector<T>> &matrix1, const std::vector<std::vector<T>> &matrix2){
    int n_rows = matrix1.size();
    int n_columns = (n_rows == 0) ? 0 : matrix1.at(0).size();
    int i, j;
    for(i = 0; i != n_rows; ++i)
        for(j = 0; j != n_columns; ++j)
            matrix1.at(i).at(j) += matrix2.at(i).at(j);
    return matrix1;
}