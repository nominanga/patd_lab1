#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Matrix* create_matrix(int rows, int cols, FieldInfo* type) {
    if (rows <= 0 || cols <= 0 || type == NULL) return NULL;

    Matrix* m = malloc(sizeof(Matrix));
    if (!m) return NULL;

    m->rows = rows;
    m->cols = cols;
    m->type = type;
    m->data = malloc(rows * sizeof(void**));
    if (!m->data) {
        free(m);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        m->data[i] = malloc(cols * sizeof(void*));
        if (!m->data[i]) {
            for (int k = 0; k < i; k++) free(m->data[k]);
            free(m->data);
            free(m);
            return NULL;
        }
        for (int j = 0; j < cols; j++) {
            m->data[i][j] = malloc(type->size);
            if (!m->data[i][j]) {
                for (int k = 0; k < j; k++) free(m->data[i][k]);
                for (int k = 0; k < i; k++) {
                    for (int l = 0; l < cols; l++) free(m->data[k][l]);
                    free(m->data[k]);
                }
                free(m->data);
                free(m);
                return NULL;
            }
            memset(m->data[i][j], 0, type->size);
        }
    }

    return m;
}

void free_matrix(Matrix* m) {
    if (!m) return;
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) free(m->data[i][j]);
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}

void set_element(Matrix* m, int i, int j, void* value) {
    if (!m || !value || i < 0 || i >= m->rows || j < 0 || j >= m->cols) return;
    m->type->set(m->data[i][j], value);
}


void print_matrix(const Matrix* m) {
    if (!m) return;
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            m->type->to_string(m->data[i][j]);
        }
        printf("\n");
    }
}

Matrix* add_matrix(const Matrix* a, const Matrix* b) {
    if (!a || !b || a->rows != b->rows || a->cols != b->cols || a->type != b->type) return NULL;

    Matrix* result = create_matrix(a->rows, a->cols, a->type);
    if (!result) return NULL;

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            void* sum = a->type->sum(a->data[i][j], b->data[i][j]);
            if (!sum) {
                free_matrix(result);
                return NULL;
            }
            set_element(result, i, j, sum);
            free(sum);
        }
    }
    return result;
}

Matrix* multiply_matrix(const Matrix* a, const Matrix* b) {
    if (!a || !b || a->cols != b->rows || a->type != b->type) return NULL;

    Matrix* result = create_matrix(a->rows, b->cols, a->type);
    if (!result) return NULL;

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            void* cell = calloc(1, a->type->size);
            if (!cell) {
                free_matrix(result);
                return NULL;
            }
            for (int k = 0; k < a->cols; k++) {
                void* product = a->type->mul(a->data[i][k], b->data[k][j]);
                if (!product) {
                    free(cell);
                    free_matrix(result);
                    return NULL;
                }
                void* new_sum = a->type->sum(cell, product);
                free(product);
                free(cell);
                cell = new_sum;
            }
            set_element(result, i, j, cell);
            free(cell);
        }
    }
    return result;
}

Matrix* transpose_matrix(const Matrix* m) {
    if (!m) return NULL;

    Matrix* result = create_matrix(m->cols, m->rows, m->type);
    if (!result) return NULL;

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            set_element(result, j, i, m->data[i][j]);
        }
    }
    return result;
}

Matrix* add_linear_combination(Matrix* matrix, int rowIndex, void* alphas) {
    if (!matrix || !alphas || rowIndex < 0 || rowIndex >= matrix->rows) return NULL;

    Matrix* result = create_matrix(matrix->rows, matrix->cols, matrix->type);
    if (!result) return NULL;

    for (int i = 0; i < matrix->rows; ++i)
        for (int j = 0; j < matrix->cols; ++j)
            set_element(result, i, j, matrix->data[i][j]);

    for (int k = 0; k < matrix->rows; ++k) {
        if (k == rowIndex) continue;

        void* alpha = (char*)alphas + k * matrix->type->size;
        for (int j = 0; j < matrix->cols; ++j) {
            void* prod = matrix->type->mul(alpha, matrix->data[k][j]);
            if (!prod) {
                free_matrix(result);
                return NULL;
            }
            void* sum = matrix->type->sum(result->data[rowIndex][j], prod);
            free(prod);
            if (!sum) {
                free_matrix(result);
                return NULL;
            }
            free(result->data[rowIndex][j]);
            result->data[rowIndex][j] = sum;
        }
    }
    return result;
}
