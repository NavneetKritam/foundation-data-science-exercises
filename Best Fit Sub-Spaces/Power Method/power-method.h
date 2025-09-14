#pragma once
template<typename T>
void display_vector(const std::vector<T> &vec);

template<typename T>
void display_matrix(const std::vector<std::vector<T>> &upper_diagonal);

std::vector<std::vector<double>> create_upper_diagonal_matrix();

std::vector<double> generate_gaussian_vector(std::vector<double> m, double v);

template<typename T>
std::vector<T>& vector_matrix_mul_inplace(const std::vector<std::vector<T>> &matrix, std::vector<T> &vec);

std::vector<double> &normalize_vector_inplace(std::vector<double> &vec);

double get_norm(const std::vector<double> &vec);

template<typename T>
std::vector<T>& subtract_vectors_inplace(std::vector<T> &first, const std::vector<T> &second);

template<typename T>
std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>> &matrix);

std::vector<double> power_method_v1(const std::vector<std::vector<double>> &matrix, const double min_error=1e-12, const int max_iterations=1e5);