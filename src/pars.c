#include "pars.h"
// PARCER

char parse_funx(char* str, int* len) {
    char ret = -1;

    if (strstr(str, "cos") == str || strstr(str, "sin") == str ||
        strstr(str, "tan") == str || strstr(str, "ln") == str) {
        *len = 3;
        ret = str[0];
        if (ret == 'l') *len = 2;
    }
    if ((ret == -1) &&
        (strstr(str, "acos") == str || strstr(str, "asin") == str ||
         strstr(str, "atan") == str || strstr(str, "sqrt") == str)) {
        *len = 4;
        ret = str[1];
        if (str[1] != 'q') ret -= 32;
    }
    if ((ret == -1) && strstr(str, "log") == str) {
        *len = 3;
        ret = 'L';
    }
    return ret;
}

char parse_bracket(char* str) {
    char ret = -1;
    if (strstr(str, "(") == str) ret = '(';
    if (strstr(str, ")") == str) ret = ')';
    return ret;
}

char parse_op(char* str, int* len) {
    char ret = -1;
    if (strstr(str, "+") == str) ret = '+';
    if (strstr(str, "-") == str) ret = '-';
    if (strstr(str, "*") == str) ret = '*';
    if (strstr(str, "/") == str) ret = '/';
    if (strstr(str, "^") == str) ret = '^';
    if (strstr(str, "mod") == str) ret = 'm';

    if (ret != -1) *len = 1;
    if (str[0] == 'm') *len = 3;
    return ret;
}

void parse_num(char* str, int* ret_len, double* ret_num, char* ret_chr) {
    *ret_len = 0;
    if (sscanf(str, "%lf %n", ret_num, ret_len) <= 0) {
        if (*str == 'x') {
            *ret_chr = 'x';
            *ret_num = 1;
            *ret_len = 1;
        } else if (*str == '+' && *(str + 1) == 'x') {
            *ret_chr = 'x';
            *ret_num = 1;
            *ret_len = 2;
        } else if (*str == '-' && *(str + 1) == 'x') {
            *ret_chr = 'x';
            *ret_num = -1;
            *ret_len = 2;
        }
    } else {
        *ret_chr = '\0';
    }
}

// POLISH NOTATION
bool validate(lex curl, lex prevl) {
    bool retval = true;
    switch (prevl.type) {
        case NUMBER:  // TODO: if '(' after numer ?
            if (curl.type != OPERATOR && curl.chr != ')') retval = false;
            break;
        case OPERATOR:
            if (curl.type != NUMBER && curl.type != FUNCTION && curl.chr != '(')
                retval = false;
            break;
        case FUNCTION:
            if (curl.chr != '(') retval = false;
            break;
        case BRACKET:
            if (prevl.chr == '(' && curl.type != NUMBER &&
                curl.type != FUNCTION)
                retval = false;
            if (prevl.chr == ')' && curl.type != OPERATOR && curl.chr != ')')
                retval = false;
            break;
        case UNDEFINED:
            if (curl.type != NUMBER && curl.type != FUNCTION && curl.chr != '(')
                retval = false;
            break;

        default:
            break;
    }
    return retval;
}

void rm_spaces(char* str) {
    char* d = str;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while ((*str++ = *d++));
}

bool op_prior_cmp(char op1, char op2) {
    int retval = false;
    int prOp1 = op_prior(op1);
    int prOp2 = op_prior(op2);

    if (prOp1 <= prOp2) {
        retval = true;
        if (op1 == '^') retval = false;  // right-accociative OPs
    }
    return retval;
}

int op_prior(char op) {
    int prior = 0;
    if (op == '+' || op == '-') prior = 1;
    if (op == '*' || op == '/' || op == 'm' || strchr("cstCSTqlL", op) != NULL)
        prior = 2;
    if (op == '^') prior = 3;
    if (op < 1) printf("\n! Prior op error ! %d\n", prior);
    return prior;
}
