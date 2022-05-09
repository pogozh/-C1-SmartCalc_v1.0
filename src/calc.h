#ifndef SRC_CALC_H_
#define SRC_CALC_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#define MODE 'm'

#define COS 'c'
#define SIN 's'
#define TAN 't'
#define ACOS 'C'
#define ASIN 'S'
#define ATAN 'T'
#define SQRT 'q'
#define LN 'l'
#define LOG 'L'

double calculate(que* exp, double x);
double calc_nums(double num1, double num2, char op);
double calc_fux(double value, char op);

#endif /* SRC_CALC_H_ */
