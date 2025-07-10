#define UNITY_INCLUDE_DOUBLE
#include "unity/unity.h"
#include "../src/matrix.h"
#include "../src/types.h"
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-6

void setUp(void) {}
void tearDown(void) {}

void assert_value_equal(const void* expected, const void* actual, FieldInfo* type) {
    if (!expected || !actual || !type) {
        TEST_FAIL_MESSAGE("Null passed");
    }

    if (type == GetIntFieldInfo()) {
        TEST_ASSERT_EQUAL_INT(*(int*)expected, *(int*)actual);
    } else if (type == GetDoubleFieldInfo()) {
        double a = *(double*)expected;
        double b = *(double*)actual;
        TEST_ASSERT_DOUBLE_WITHIN(EPSILON, a, b);
    } else if (type == GetComplexFieldInfo()) {
        Complex a = *(Complex*)expected;
        Complex b = *(Complex*)actual;
        TEST_ASSERT_DOUBLE_WITHIN(EPSILON, a.real, b.real);
        TEST_ASSERT_DOUBLE_WITHIN(EPSILON, a.img, b.img);
    } else {
        TEST_FAIL_MESSAGE("Unknown type");
    }
}

void assert_matrix_equal(const Matrix* expected, const Matrix* actual) {
    TEST_ASSERT_NOT_NULL(expected);
    TEST_ASSERT_NOT_NULL(actual);
    TEST_ASSERT_EQUAL_PTR(expected->type, actual->type);
    TEST_ASSERT_EQUAL_INT(expected->rows, actual->rows);
    TEST_ASSERT_EQUAL_INT(expected->cols, actual->cols);

    for (int i = 0; i < expected->rows; ++i) {
        for (int j = 0; j < expected->cols; ++j) {
            assert_value_equal(expected->data[i][j], actual->data[i][j], expected->type);
        }
    }
}


// creation
void test_create_matrix_int(void) {
    Matrix* m = create_matrix(2, 2, GetIntFieldInfo());
    TEST_ASSERT_NOT_NULL(m);
    free_matrix(m);
}

void test_create_matrix_double(void) {
    Matrix* m = create_matrix(2, 2, GetDoubleFieldInfo());
    TEST_ASSERT_NOT_NULL(m);
    free_matrix(m);
}

void test_create_matrix_complex(void) {
    Matrix* m = create_matrix(2, 2, GetComplexFieldInfo());
    TEST_ASSERT_NOT_NULL(m);
    free_matrix(m);
}

// sum
void test_add_matrix_int(void) {
    FieldInfo* type = GetIntFieldInfo();
    Matrix* a = create_matrix(2, 2, type);
    Matrix* b = create_matrix(2, 2, type);
    int va[] = {1, 2, 3, 4};
    int vb[] = {5, 6, 7, 8};
    int ve[] = {6, 8, 10, 12};

    for (int i = 0; i < 4; i++) {
        set_element(a, i/2, i%2, &va[i]);
        set_element(b, i/2, i%2, &vb[i]);
    }

    Matrix* result = add_matrix(a, b);
    Matrix* expected = create_matrix(2, 2, type);

    for (int i = 0; i < 4; i++) {
        set_element(expected, i/2, i%2, &ve[i]);
    }

    assert_matrix_equal(expected, result);
    free_matrix(a); free_matrix(b); free_matrix(result); free_matrix(expected);
}

void test_add_matrix_double(void) {
    FieldInfo* type = GetDoubleFieldInfo();
    Matrix* a = create_matrix(1, 2, type);
    Matrix* b = create_matrix(1, 2, type);
    double va[] = {1.5, 2.5};
    double vb[] = {0.5, 3.5};
    double ve[] = {2.0, 6.0};

    for (int i = 0; i < 2; i++) {
        set_element(a, 0, i, &va[i]);
        set_element(b, 0, i, &vb[i]);
    }

    Matrix* result = add_matrix(a, b);
    Matrix* expected = create_matrix(1, 2, type);

    for (int i = 0; i < 2; i++) {
        set_element(expected, 0, i, &ve[i]);
    }

    assert_matrix_equal(expected, result);
    free_matrix(a); free_matrix(b); free_matrix(result); free_matrix(expected);
}

void test_add_matrix_complex(void) {
    FieldInfo* type = GetComplexFieldInfo();
    Matrix* a = create_matrix(1, 1, type);
    Matrix* b = create_matrix(1, 1, type);
    Complex va = {1.0, 2.0};
    Complex vb = {3.0, 4.0};
    Complex ve = {4.0, 6.0};

    set_element(a, 0, 0, &va);
    set_element(b, 0, 0, &vb);

    Matrix* result = add_matrix(a, b);
    Matrix* expected = create_matrix(1, 1, type);
    set_element(expected, 0, 0, &ve);

    assert_matrix_equal(expected, result);
    free_matrix(a); free_matrix(b); free_matrix(result); free_matrix(expected);
}

// product
void test_multiply_matrix_int(void) {
    FieldInfo* type = GetIntFieldInfo();
    Matrix* a = create_matrix(2, 2, type);
    Matrix* b = create_matrix(2, 2, type);
    int va[] = {1, 2, 3, 4};
    int vb[] = {2, 0, 1, 2};
    int ve[] = {4, 4, 10, 8};

    for (int i = 0; i < 4; i++) {
        set_element(a, i/2, i%2, &va[i]);
        set_element(b, i/2, i%2, &vb[i]);
    }

    Matrix* result = multiply_matrix(a, b);
    Matrix* expected = create_matrix(2, 2, type);

    for (int i = 0; i < 4; i++) {
        set_element(expected, i/2, i%2, &ve[i]);
    }

    assert_matrix_equal(expected, result);
    free_matrix(a); free_matrix(b); free_matrix(result); free_matrix(expected);
}

void test_multiply_matrix_double(void) {
    FieldInfo* type = GetDoubleFieldInfo();
    Matrix* a = create_matrix(2, 2, type);
    Matrix* b = create_matrix(2, 2, type);
    double va[] = {1.5, 2.5, 3.5, 4.5};
    double vb[] = {2.0, 0.5, 1.5, 2.5};
    double ve[] = {6.75, 7.0, 13.75, 13.0};

    for (int i = 0; i < 4; i++) {
        set_element(a, i/2, i%2, &va[i]);
        set_element(b, i/2, i%2, &vb[i]);
    }

    Matrix* result = multiply_matrix(a, b);
    Matrix* expected = create_matrix(2, 2, type);

    for (int i = 0; i < 4; i++) {
        set_element(expected, i/2, i%2, &ve[i]);
    }

    assert_matrix_equal(expected, result);
    free_matrix(a); free_matrix(b); free_matrix(result); free_matrix(expected);
}

void test_multiply_matrix_complex(void) {
    FieldInfo* type = GetComplexFieldInfo();
    Matrix* a = create_matrix(2, 2, type);
    Matrix* b = create_matrix(2, 2, type);

    Complex va[] = {
        {1, 2}, {3, 4},
        {5, 6}, {7, 8}
    };
    Complex vb[] = {
        {1, -1}, {2, 0},
        {0, 2}, {3, 1}
    };
    Complex ve[] = {
        {-5, 7}, {7, 19},
        {-5, 15}, {23, 43}
    };

    for (int i = 0; i < 4; i++) {
        set_element(a, i / 2, i % 2, &va[i]);
        set_element(b, i / 2, i % 2, &vb[i]);
        set_element(b, i / 2, i % 2, &vb[i]); 
    }

    Matrix* result = multiply_matrix(a, b);
    Matrix* expected = create_matrix(2, 2, type);

    for (int i = 0; i < 4; i++) {
        set_element(expected, i / 2, i % 2, &ve[i]);
    }

    assert_matrix_equal(expected, result);
    free_matrix(a); free_matrix(b); free_matrix(result); free_matrix(expected);
}



//transpose
void test_transpose_matrix_int(void) {
    FieldInfo* type = GetIntFieldInfo();
    Matrix* m = create_matrix(2, 3, type);
    int vals[] = {1, 2, 3, 4, 5, 6};

    for (int i = 0; i < 6; ++i)
        set_element(m, i / 3, i % 3, &vals[i]);

    Matrix* transposed = transpose_matrix(m);
    Matrix* expected = create_matrix(3, 2, type);
    int expectedVals[] = {1, 4, 2, 5, 3, 6};

    for (int i = 0; i < 6; ++i)
        set_element(expected, i / 2, i % 2, &expectedVals[i]);

    assert_matrix_equal(expected, transposed);
    free_matrix(m);
    free_matrix(transposed);
    free_matrix(expected);
}



//linear combination
void test_linear_combination_double(void) {
    FieldInfo* type = GetDoubleFieldInfo();
    Matrix* m = create_matrix(3, 2, type);
    double row0[] = {1.0, 2.0};
    double row1[] = {3.0, 4.0};
    double row2[] = {5.0, 6.0};

    for (int i = 0; i < 2; ++i) {
        set_element(m, 0, i, &row0[i]);
        set_element(m, 1, i, &row1[i]);
        set_element(m, 2, i, &row2[i]);
    }

    double alphas[] = {0.0, 2.0, -1.0};
    Matrix* result = add_linear_combination(m, 0, alphas);

    double expected[] = {2.0, 4.0};
    for (int i = 0; i < 2; ++i) {
        double actual = *(double*)result->data[0][i];
        TEST_ASSERT_DOUBLE_WITHIN(EPSILON, expected[i], actual);
    }

    free_matrix(m);
    free_matrix(result);
}



// universal
void test_type_mismatch(void) {
    Matrix* a = create_matrix(2, 2, GetIntFieldInfo());
    Matrix* b = create_matrix(2, 2, GetDoubleFieldInfo());
    Matrix* result = add_matrix(a, b);
    TEST_ASSERT_NULL(result);
    free_matrix(a);
    free_matrix(b);
}

void test_multiply_matrix_wrong_dimensions(void) {
    Matrix* a = create_matrix(2, 3, GetIntFieldInfo());
    Matrix* b = create_matrix(2, 2, GetIntFieldInfo()); 
    Matrix* result = multiply_matrix(a, b);
    TEST_ASSERT_NULL(result);
    free_matrix(a);
    free_matrix(b);
}

void test_set_element_out_of_bounds(void) {
    Matrix* m = create_matrix(2, 2, GetIntFieldInfo());

    int vals[4] = {1, 2, 3, 4};
    for (int i = 0; i < 4; ++i)
        set_element(m, i / 2, i % 2, &vals[i]);

    int invalid = 99;
    set_element(m, 10, 10, &invalid);

    for (int i = 0; i < 4; ++i) {
        int actual = ((integer_t*)m->data[i / 2][i % 2])->value;
        TEST_ASSERT_EQUAL_INT(vals[i], actual);
    }

    free_matrix(m);
}





int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_create_matrix_int);
    RUN_TEST(test_create_matrix_double);
    RUN_TEST(test_create_matrix_complex);
    RUN_TEST(test_add_matrix_int);
    RUN_TEST(test_add_matrix_double);
    RUN_TEST(test_add_matrix_complex);
    RUN_TEST(test_multiply_matrix_int);
    RUN_TEST(test_multiply_matrix_double);
    RUN_TEST(test_multiply_matrix_complex);
    RUN_TEST(test_type_mismatch);
    RUN_TEST(test_multiply_matrix_wrong_dimensions);
    RUN_TEST(test_set_element_out_of_bounds);
    RUN_TEST(test_linear_combination_double);
    return UNITY_END();
}
