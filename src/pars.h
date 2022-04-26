#ifndef SRC_PARS_H_
#define SRC_PARS_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

#define s21_INFINITY 1.0 / 0.0
#define s21_NEG_INFINITY -1.0 / 0.0
#define s21_NAN 0.0 / 0.0

#define SIN 801.0
#define COS 802.0
#define ASIN 811.0
#define ACOS 812.0
#define TAN 820.0
#define ATAN 821.0
#define SQRT 830.0
#define LOG 840.0
#define LN 850.0
#define POW 700.0
#define MOD 600.0
#define MUL 500.0
#define DEF 501.0
#define PLUS 400.0
#define MINUS 401.0
#define OPEN_BRACKET 300.0
#define CLOSE_BRACKET 200.0

// main function
double calculation(char *exprassion);

// utils
int gocalc(stack_t *opers, stack_t *nums);
int oper_priority(char oper);
int funx_priority(int oper);
int check_repeated_opers(char *str);
int pars_n_add_ops(stack_t *opers, char *string, int i);
int unary_oper(char *str, int i);
int is_digit(char chr);
int is_number(char *str, int i);
int valid_tail(char *str, int len);
double stack_down_to_result(stack_t *opers, stack_t *nums);

#include "stack.h"
#endif  // SRC_PARS_H_
