#include "types.h"
#include <stdio.h>
#include <stdlib.h>

void set_int(void* dest, void* value) {
    *(int*)dest = *((int*)value);
}

void* sum_int(void* a, void* b) {
    int* result = malloc(sizeof(int));
    if (!result) return NULL;
    *result = *(int*)a + *(int*) b;
    return result;
}

void* mul_int(void* a, void* b) {
    int* result = malloc(sizeof(int));
    if (!result) return NULL;
    *result = *(int*)a * *(int*) b;
    return result;
}

void to_string_int(void* element) {
    printf("%d ", *(int*) element);
}




void set_double(void* dest, void* value) {
    *(double*)dest = *((double*)value);
}

void* sum_double(void* a, void* b) {
    double* result = malloc(sizeof(double));
    if (!result) return NULL;
    *result = (*(double*)a) + (*(double*)b);
    return result;
}

void* mul_double(void* a, void* b) {
    double* result = malloc(sizeof(double));
    if (!result) return NULL;
    *result = (*(double*)a) * (*(double*)b);
    return result;
}

void to_string_double(void* element) {
    printf("%lf ", *(double*) element);
}




void set_complex(void* dest, void* value) {
    *(Complex*)dest = *((Complex*)value);
}

void* sum_complex(void* a, void* b) {
    Complex* result = malloc(sizeof(Complex));
    if (!result) return NULL;
    *result = get_complex_sum(*(Complex*) a, *(Complex*) b);
    return result;
}

void* mul_complex(void* a, void* b) {
    Complex* result = malloc(sizeof(Complex));
    if (!result) return NULL;
    *result = get_complex_product(*(Complex*) a, *(Complex*) b);
    return result;
}

void to_string_complex(void* element) {
    Complex val = *(Complex*)element; 
    printf("%.2lf + %.2lfi ", val.real, val.img);
}





static FieldInfo* INT_FIELD_INFO = NULL;
static FieldInfo* DOUBLE_FIELD_INFO = NULL;
static FieldInfo* COMPLEX_FIELD_INFO = NULL;

FieldInfo* GetIntFieldInfo() {
    if (!INT_FIELD_INFO) {
        INT_FIELD_INFO = malloc(sizeof(FieldInfo));
        INT_FIELD_INFO->size = sizeof(int);
        INT_FIELD_INFO->to_string = to_string_int;
        INT_FIELD_INFO->sum = sum_int;
        INT_FIELD_INFO->mul = mul_int;
        INT_FIELD_INFO->set = set_int;
    }
    return INT_FIELD_INFO;
}

FieldInfo* GetDoubleFieldInfo() {
    if (!DOUBLE_FIELD_INFO) {
        DOUBLE_FIELD_INFO = malloc(sizeof(FieldInfo));
        DOUBLE_FIELD_INFO->size = sizeof(double);
        DOUBLE_FIELD_INFO->to_string = to_string_double;
        DOUBLE_FIELD_INFO->sum = sum_double;
        DOUBLE_FIELD_INFO->mul = mul_double;
        DOUBLE_FIELD_INFO->set = set_double;
    }
    return DOUBLE_FIELD_INFO;
}

FieldInfo* GetComplexFieldInfo() {
    if (!COMPLEX_FIELD_INFO) {
        COMPLEX_FIELD_INFO = malloc(sizeof(FieldInfo));
        COMPLEX_FIELD_INFO->size = sizeof(Complex);
        COMPLEX_FIELD_INFO->to_string = to_string_complex;
        COMPLEX_FIELD_INFO->sum = sum_complex;
        COMPLEX_FIELD_INFO->mul = mul_complex;
        COMPLEX_FIELD_INFO->set = set_complex;
    }
    return COMPLEX_FIELD_INFO;
}

