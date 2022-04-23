#ifndef SRC_STACK_PARS_H_
#define SRC_STACK_PARS_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#define s21_INFINITY 1.0 / 0.0
#define s21_NEG_INFINITY -1.0 / 0.0
#define s21_NAN 0.0 / 0.0

#define SIN 701
#define COS 702
#define ASIN 711
#define ACOS 712
#define TAN 780
#define ATAN 781
#define SQRT 760
#define LOG 750
#define LN 751
#define POW 600
#define MOD 400
#define MUL 300
#define DEF 301
#define PLUS 200
#define MINUS 201
#define CLOSE_BRACKET 100
#define OPEN_BRaCKET 000

int oper_priority(stack_t oper);

#include "stack.h"
#endif /* SRC_STACK_PARS_H_ */