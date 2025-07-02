#ifndef MATRIX_H
#define MATRIX_H

#include "types.h"     
#include "complex.h"   

typedef struct {
    int rows;
    int cols;
    FieldInfo* type;
    void*** data;
} Matrix;

Matrix* create_matrix(int rows, int cols, FieldInfo* type);
void free_matrix(Matrix* m);

void set_element(Matrix* m, int i, int j, void* value);

void print_matrix(const Matrix* m);

Matrix* add_matrix(const Matrix* a, const Matrix* b);
Matrix* multiply_matrix(const Matrix* a, const Matrix* b);
Matrix* transpose_matrix(const Matrix* m);

Matrix* add_linear_combination(Matrix* matrix, int rowIndex, void* alphas);

#endif
