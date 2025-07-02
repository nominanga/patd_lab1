#include "complex.h"
#include <stdlib.h>
#include <stdio.h>

Complex get_complex_sum(const Complex c1, const Complex c2) {
    Complex res = {c1.real + c2.real, c1.img + c2.img};
    return res;
}

Complex get_complex_product(const Complex c1, const Complex c2) {
    double real = c1.real * c2.real - c1.img * c2.img;
    double img = c1.real * c2.img + c1.img * c2.real;
    Complex res = {real, img};
    return res;
}
