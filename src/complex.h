#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct {
    double real;
    double img;
} Complex;

Complex get_complex_sum(const Complex c1, const Complex c2);
Complex get_complex_product(const Complex c1, const Complex c2);

// void print_complex(const Complex c);

#endif


