#include "types.h"
#include <stdio.h>
#include <stdlib.h>

void set_int(void* dest, void* value) {
    ((integer_t*)dest)->value = *((int*)value);
}

void* sum_int(void* a, void* b) {
    integer_t* result = malloc(sizeof(integer_t));
    if (!result) return NULL;
    result->value = ((integer_t*)a)->value + ((integer_t*)b)->value;
    return result;
}

void* mul_int(void* a, void* b) {
    integer_t* result = malloc(sizeof(integer_t));
    if (!result) return NULL;
    result->value = ((integer_t*)a)->value * ((integer_t*)b)->value;
    return result;
}

void to_string_int(void* element) {
    printf("%d ", ((integer_t*)element)->value);
}




void set_double(void* dest, void* value) {
    ((my_double_t*)dest)->value = *((double*)value);
}

void* sum_double(void* a, void* b) {
    my_double_t* result = malloc(sizeof(my_double_t));
    if (!result) return NULL;
    result->value = ((my_double_t*)a)->value + ((my_double_t*)b)->value;
    return result;
}

void* mul_double(void* a, void* b) {
    my_double_t* result = malloc(sizeof(my_double_t));
    if (!result) return NULL;
    result->value = ((my_double_t*)a)->value * ((my_double_t*)b)->value;
    return result;
}

void to_string_double(void* element) {
    printf("%lf ", ((my_double_t*)element)->value);
}




void set_complex(void* dest, void* value) {
    ((complex_t*)dest)->value = *((Complex*)value);
}

void* sum_complex(void* a, void* b) {
    complex_t* result = malloc(sizeof(complex_t));
    if (!result) return NULL;
    result->value = get_complex_sum(((complex_t*)a)->value, ((complex_t*)b)->value);
    return result;
}

void* mul_complex(void* a, void* b) {
    complex_t* result = malloc(sizeof(complex_t));
    if (!result) return NULL;
    result->value = get_complex_product(((complex_t*)a)->value, ((complex_t*)b)->value);
    return result;
}

void to_string_complex(void* element) {
    Complex val = ((complex_t*)element)->value;
    printf("%.2lf + %.2lfi ", val.real, val.img);
}





static FieldInfo* INT_FIELD_INFO = NULL;
static FieldInfo* DOUBLE_FIELD_INFO = NULL;
static FieldInfo* COMPLEX_FIELD_INFO = NULL;

FieldInfo* GetIntFieldInfo() {
    if (!INT_FIELD_INFO) {
        INT_FIELD_INFO = malloc(sizeof(FieldInfo));
        INT_FIELD_INFO->size = sizeof(integer_t);
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
        DOUBLE_FIELD_INFO->size = sizeof(my_double_t);
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
        COMPLEX_FIELD_INFO->size = sizeof(complex_t);
        COMPLEX_FIELD_INFO->to_string = to_string_complex;
        COMPLEX_FIELD_INFO->sum = sum_complex;
        COMPLEX_FIELD_INFO->mul = mul_complex;
        COMPLEX_FIELD_INFO->set = set_complex;
    }
    return COMPLEX_FIELD_INFO;
}

