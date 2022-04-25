#include "pars.h"

double calculation(char *input) {
    double result = NAN;
    stack_t nums = create_stack();
    stack_t opers = create_stack();
    printf("debag calculation...\n");

    int inpLen = strlen(input);
    int skip = check_repeated_opers(input);
    if (!skip) skip = !valid_tail(input, inpLen);
    if (skip == true) {
        printf("\n ! error: operator repeated or validation faild \n");
    } else {
        for (int i = 0; i < inpLen; i++) {
            int unary = 0;
            int flag = false;
            i = check_functions(&opers, input, i);
            if ((is_digit(input[i]) == false) &&
                (unary = unary_oper(input, i) < 0))
                flag = true;
            // printf("count unary= %d, flag = %d...\n", unary, flag);

            // find numbers
            if (is_digit(input[i])) {
                double number = 0.0;
                while (is_digit(input[i]) == true) {
                    number *= 10;
                    number += input[i] - '0';
                    i++;
                }
                if (input[i] == '.' || input[i] == ',') {
                    i++;
                    double tail = 0.0, multiply = 1.0;
                    while (is_digit(input[i]) == true) {
                        tail += (double)(input[i] - '0') / powl(10.0, multiply);
                        multiply++;
                        i++;
                    }
                    i--;
                    // result float num to push
                    number += tail;
                }
                if (unary == true) number *= -1.0;
                printf("%f\n", number);
                push(&nums, number);
            }
        }
    }

    stack_print(&opers);
    stack_print(&nums);
    // debag end
    stack_delete(&nums);
    stack_delete(&opers);
    result = 2;  // TODO: !!! DELETE !!!
    return result;
}

int oper_priority(stack_t oper) {
    int priority = (int)oper.data[oper.top] / 100;
    if (priority > 9 || priority < 0) priority = -1;
    return priority;
}

int check_repeated_opers(char *str) {
    int repeat = false;
    int inpLen = strlen(str);
    for (int i = 0; i < (inpLen - 1); i++) {
        if ((str[i] == '*' || str[i] == '/' || str[i] == '%' || str[i] == '^' ||
             str[i] == '+' || str[i] == '-') &&
            (str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '%' ||
             str[i + 1] == '^'))
            repeat = true;
    }
    // printf("str = %s, repeat = %d \n", str, repeat);
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
        } else if (!strncmp("sin(", str + i, 3)) {
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
// TODO: make batter with epxr like '-sin(-1)'
int unary_oper(char *str, int i) {
    int unary = false;
    if ((i > 0 && (is_digit(str[i - 1]) == false) && str[i - 1] == '(') ||
        ((i == 0) && is_digit(str[i + 1]) == true)) {
        if (str[i] == '+')
            unary = 1;
        else if (str[i] == '-')
            unary = -1;
    }

    return unary;
}

int is_digit(char chr) {
    int digit = true;
    if ((chr == '\0') || (chr > '9' || chr < '0')) {
        digit = false;
    }
    return digit;
}

int is_number(char *str, int i) {
    bool result = true;
    if ((is_digit(str[i] = false) && str[i] != '.' && str[i] != ',') ||
        ((str[i] == '.' || str[i] == ',') &&
         ((is_digit(str[i + 1]) == false) && i > 0 &&
          (is_digit(str[i - 1]) == false)))) {
        result = false;
    }
    return result;
}

int valid_tail(char *str, int len) {
    int valid = true;
    if (len > 1 && is_digit(str[len - 1]) == false && str[len - 1] != ')' &&
        str[len - 1] != '.')
        valid = false;
    // printf("str[len - 1] = %c | valid = %d\n", str[len - 1], valid);
    return valid;
}