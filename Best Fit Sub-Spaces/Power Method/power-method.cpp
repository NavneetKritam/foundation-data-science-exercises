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

