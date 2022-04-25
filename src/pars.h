#ifndef SRC_STACK_PARS_H_
#define SRC_STACK_PARS_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#define s21_INFINITY 1.0 / 0.0
#define s21_NEG_INFINITY -1.0 / 0.0
#define s21_NAN 0.0 / 0.0

#define SIN 801
#define COS 802
#define ASIN 811
#define ACOS 812
#define TAN 820
#define ATAN 821
#define SQRT 830
#define LOG 840
#define LN 850
#define POW 700
#define MOD 600
#define MUL 500
#define DEF 501
#define PLUS 400
#define MINUS 401
#define CLOSE_BRACKET 300
#define OPEN_BRACKET 200

int oper_priority(stack_t oper);

#include "stack.h"
#endif /* SRC_STACK_PARS_H_ */