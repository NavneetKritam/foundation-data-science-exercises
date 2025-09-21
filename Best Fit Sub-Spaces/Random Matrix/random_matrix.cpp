#include"random_matrix.h"

int main(){
    int n_rows = 100, n_columns = 100; // Working with 100*100 matrix
    // Get 100*100 matrix with x~[0, 1] entries
    std::vector<std::vector<double>> random_matrix = construct_random_matrix(n_rows, n_columns);
    printf("Constructed\n");
    double complete_frobenius = frobenius_norm(random_matrix), partial_frobenius; // Calculate complete Frobenius Norm 
    int k = 10; // Number of Singular Vectors 
    std::vector<std::vector<double>> singular_vectors = power_method(random_matrix, k); // Get 10 singular vs
    printf("First 10 singular vectors fetch completed\n");
    // Partial Matrix to store \sigma*u*vT initially zero matrix
    std::vector<std::vector<double>> partial_matrix(n_rows, std::vector<double>(n_columns, 0.0));
    int i; // Iterator integer
    for(i = 0; i != k; ++i){
        // Getting kth \sigma * ui * viT and accumulating in partial_matrix
        partial_matrix = matrix_addition_inplace(partial_matrix, get_matrix_component(random_matrix, singular_vectors.at(i)));
        partial_frobenius = frobenius_norm(partial_matrix);
        printf("%.2lf Frobenius norm accumulated in first %d singular vectors\n", partial_frobenius / complete_frobenius * 100.0, i + 1);
    }
    return 0;
}