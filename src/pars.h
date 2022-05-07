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

// parser
char parse_funx(char* str, int* len);
char parse_bracket(char* str);
char parse_op(char* str, int* len);
void parse_num(char* str, int* ret_len, double* ret_num, char* ret_chr);
// notation
bool op_prior_cmp(char op1, char op2);
int op_prior(char op);
void rm_spaces(char* str);
bool validate(lex curl, lex prevl);
// utils

#include "stack.h"
#endif  // SRC_PARS_H_
