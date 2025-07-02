#include "matrix.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    FieldInfo* intType = GetIntFieldInfo();
    if (!intType) {
        printf("Failed to initialize FieldInfo for integers\n");
        return 1;
    }

    int a_val = 1, b_val = 2, c_val = 3, d_val = 4;

    Matrix* A = create_matrix(2, 2, intType);
    Matrix* B = create_matrix(2, 2, intType);

    if (!A || !B) {
        printf("Matrix allocation failed\n");
        return 1;
    }

    set_element(A, 0, 0, &a_val);
    set_element(A, 0, 1, &b_val);
    set_element(A, 1, 0, &c_val);
    set_element(A, 1, 1, &d_val);

    set_element(B, 0, 0, &d_val);
    set_element(B, 0, 1, &c_val);
    set_element(B, 1, 0, &b_val);
    set_element(B, 1, 1, &a_val);

    printf("Matrix A:\n");
    print_matrix(A);

    printf("Matrix B:\n");
    print_matrix(B);

    Matrix* sum = add_matrix(A, B);
    printf("A + B:\n");
    print_matrix(sum);

    Matrix* prod = multiply_matrix(A, B);
    printf("A * B:\n");
    print_matrix(prod);

    Matrix* trans = transpose_matrix(A);
    printf("Transpose of A:\n");
    print_matrix(trans);

    int alphas[] = {0, 2};
    Matrix* linear = add_linear_combination(A, 0, alphas);
    printf("After adding linear combination to row 0 (alpha = {0, 2}):\n");
    print_matrix(linear);

    
    free_matrix(A);
    free_matrix(B);
    free_matrix(sum);
    free_matrix(prod);
    free_matrix(trans);
    free_matrix(linear);

    return 0;
}