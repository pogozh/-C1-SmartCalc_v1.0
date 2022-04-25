#include "pars.h"

double calculation(char *input) {
    double result = NAN;
    stack_t nums = create_stack();
    stack_t opers = create_stack();
    int inpLen = strlen(input);
    char element = '\0';
    int skip = false;
    for (int i = 0; i < inpLen; i++) {
        element = input[i];
        skip = check_repeated_opers(element);
    }
    if (skip == false) {
        printf("debag calculation...\n");
        int flag = false, unary = false;
        for (int i = 0; i < inpLen; i++) {
            i = check_functions(&opers, input, i);
            // debag
            printf("cunt unary= %d, flag = %d...\n", flag, unary);
            if (!('0' <= input[i] && input[i] <= '9')) {
                unary = unary_minus(input, i);
                if (unary > 0) {
                    flag = 1;
                } else {
                    flag = 0;
                }
            }
        }
    }

    stack_print(&opers);
    // debag end
    stack_delete(&nums);
    stack_delete(&opers);
    return result;
}

int oper_priority(stack_t oper) {
    int priority = (int)oper.data[oper.top] / 100;
    if (priority > 9 || priority < 0) priority = -1;

    return priority;
}

int check_repeated_opers(const char element) {
    int repeat = false;
    if (element == '*' || element == '/' || element == '%' || element == '^' ||
        element == '+' || element == '-') {
        if (element == '*' || element == '/' || element == '%' ||
            element == '^') {
            repeat = true;
        }
    }
    return repeat;
}

// TODO: add 1 symbol
int check_functions(stack_t *opers, char *str, int i) {
    if (str[i] >= 'a' && str[i] <= 'z') {
        if (!strncmp("log(", str + i, 3)) {
            i += 3;
            push(opers, LOG);
        } else if (!strncmp("ln(", str + i, 2)) {
            i += 2;
            push(opers, LN);
        } else if (!strncmp("sqrt(", str + i, 4)) {
            i += 4;
            push(opers, SQRT);
        } else if (!strncmp("atan(", str + i, 4)) {
            i += 4;
            push(opers, ATAN);
        } else if (!strncmp("acos(", str + i, 4)) {
            i += 4;
            push(opers, ACOS);
        } else if (!strncmp("asin(", str + i, 4)) {
            i += 4;
            push(opers, ASIN);
        } else if (!strncmp("tan(", str + i, 3)) {
            i += 3;
            push(opers, TAN);
        } else if (!strncmp("sin(", str + i, 4)) {
            // printf("\nsin( = %s\n", (str + i));
            i += 3;
            push(opers, SIN);
        } else if (!strncmp("cos(", str + i, 3)) {
            i += 3;
            push(opers, COS);
        }
    }
    return i;
}

int unary_minus(char *str, int i) {
    int unary = false;
    if (str[i] == '-' && !('0' <= str[i - 1] && str[i - 1] <= '9') &&
        str[i - 1] != ')') {
        unary = true;
    } else if (str[i] == '+' && !('0' <= str[i - 1] && str[i - 1] <= '9') &&
               str[i - 1] != ')') {
        unary = -1; /* error */
    }
    return unary;
}