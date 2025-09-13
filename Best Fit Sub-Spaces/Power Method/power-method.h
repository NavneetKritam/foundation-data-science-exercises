#pragma once
template<typename T>
void display_vector(const std::vector<T> &vec);

template<typename T>
void display_matrix(const std::vector<std::vector<T>> &upper_diagonal);

std::vector<std::vector<int>> create_upper_diagonal_matrix();

std::vector<float> generate_gaussian_vector(std::vector<float> m, float v);
