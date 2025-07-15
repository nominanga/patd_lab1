#ifndef TYPES_H
#define TYPES_H

#include "complex.h"
#include <stddef.h>

typedef struct FieldInfo {
    size_t size;
    void (*to_string)(void *element);
    void* (*sum)(void* a, void* b);
    void* (*mul)(void* a, void* b);
    void (*set)(void* dest, void* value);
} FieldInfo;

FieldInfo* GetIntFieldInfo();
FieldInfo* GetDoubleFieldInfo();
FieldInfo* GetComplexFieldInfo();

// избавиться от всего лишнего

void set_int(void* dest, void* value);
void* sum_int(void* a, void* b);
void* mul_int(void* a, void* b);
void to_string_int(void* element);

void set_double(void* dest, void* value);
void* sum_double(void* a, void* b);
void* mul_double(void* a, void* b);
void to_string_double(void* element);

void set_complex (void* dest, void* value);
void* sum_complex(void* a, void* b);
void* mul_complex(void* a, void* b);
void to_string_complex(void* element);


#endif