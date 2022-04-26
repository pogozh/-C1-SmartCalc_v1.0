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
            i = pars_n_add_ops(&opers, input, i);
            if ((is_digit(input[i]) == false) &&
                (unary = unary_oper(input, i) < 0))
                flag = true;
            // printf("count unary= %d, flag = %d...\n", unary, flag);

            // find numbers
            if (is_digit(input[i])) {
                double number = 0.0;
                while (is_digit(input[i])) {
                    number *= 10;
                    number += input[i] - '0';
                    i++;
                }
                if (input[i] == '.') {
                    i++;
                    double tail = 0.0, multiply = 1.0;
                    while (is_digit(input[i])) {
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
            } else if (flag == false) {
                int prior = oper_priority(input[i]);
                if (prior > 1 && prior < 9) {
                    /* if close bracket*/
                    if (prior == 2) {
                        while (opers.top > 0 &&
                               funx_priority(opers.data[opers.top - 1]) != 3) {
                            gocalc(&opers, &nums);
                        }
                        pop(&opers);
                    } else if (opers.top > 0 &&
                               prior <=
                                   funx_priority(opers.data[opers.top - 1]) &&
                               prior != 3) {
                        gocalc(&opers, &nums);
                        pars_n_add_ops(&opers, input, i);
                    } else {
                        pars_n_add_ops(&opers, input, i);
                    }
                }
            }
        }
    }

    stack_print(&opers);
    stack_print(&nums);

    result = stack_down_to_result(&opers, &nums);

    // debag end
    stack_delete(&nums);
    stack_delete(&opers);
    return result;
}

double stack_down_to_result(stack_t *opers, stack_t *nums) {
    double result = 0.0;
    while ((opers->top) > 0) {
        if (funx_priority(opers->data[opers->top]) >= 1 ||
            funx_priority(opers->data[opers->top]) <= 7) {
            if (funx_priority(opers->data[opers->top]) == 0) {
                while (funx_priority(opers->data[opers->top]) == 1) {
                    result = gocalc(opers, nums);
                }
                pop(opers);
            } else if (opers->top > 1 &&
                       funx_priority(opers->data[opers->top - 1]) <
                           funx_priority(opers->data[opers->top - 2])) {
                result = gocalc(opers, nums);
            } else if (funx_priority(opers->data[opers->top]) ==
                       funx_priority(opers->data[opers->top])) {
                result = gocalc(opers, nums);
            }
        }
    }
    return result;
}

int gocalc(stack_t *opers, stack_t *nums) {
    double num1 = pop(nums);
    double num2 = 0.0;
    double result = 0.0;
    int op = pop(opers);
    if (op == MINUS) {
        num2 = pop(nums);
        result = num2 - num1;
    } else if (op == PLUS) {
        num2 = pop(nums);
        result = num2 + num1;
    } else if (op == MUL) {
        num2 = pop(nums);
        result = num2 * num1;
    } else if (op == DEF) {
        num2 = pop(nums);
        result = num2 / num1;
    } else if (op == POW) {
        num2 = pop(nums);
        result = pow(num2, num1);
    } else if (op == MOD) {
        num2 = pop(nums);
        result = fmod(num2, num1);
    } else if (op == LN) {
        num2 = pop(nums);
        result = log10(num1);
    } else if (op == SQRT) {
        num2 = pop(nums);
        result = sqrt(num1);
    } else if (op == ATAN) {
        num2 = pop(nums);
        result = atan(num1);
    } else if (op == ACOS) {
        num2 = pop(nums);
        result = acosl(num1);
    } else if (op == ASIN) {
        num2 = pop(nums);
        result = asin(num1);
    } else if (op == TAN) {
        num2 = pop(nums);
        result = tan(num1);
    } else if (op == SIN) {
        num2 = pop(nums);
        result = sin(num1);
    } else if (op == COS) {
        num2 = pop(nums);
        result = cos(num1);
    }

    push(nums, result);
    return result;
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

int oper_priority(char oper) {
    int priority = -2;
    if (oper == ')') {
        priority = 2;
    } else if (oper == '(') {
        priority = 3;
    } else if (oper == '+' || oper == '-') {
        priority = 4;
    } else if (oper == '*' || oper == '/') {
        priority = 5;
    } else if ((oper == '%') || (oper == 'M') || (oper == 'm')) {
        priority = 6;
    } else if (oper == '^') {
        priority = 7;
    } else if (oper == 'L' || oper == 'l' || oper == 'S' || oper == 'T' ||
               oper == 'C' || oper == 'A' || oper == 't' || oper == 's' ||
               oper == 'c') {
        priority = 8;
    } else {
        priority = -1;
    }
    return priority;
}

// TODO: add 1 symbol
int pars_n_add_ops(stack_t *opers, char *str, int i) {
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
        if (str[i] == '-') push(opers, MINUS);
        if (str[i] == '+') push(opers, PLUS);
        if (str[i] == '*') push(opers, MUL);
        if (str[i] == '/') push(opers, DEF);
        if (str[i] == '%') push(opers, MOD);
        if (str[i] == '^') push(opers, POW);
        if (str[i] == ')') push(opers, CLOSE_BRACKET);
        if (str[i] == '(') push(opers, OPEN_BRACKET);
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

// needs ?
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

// no needs
int funx_priority(int oper) {
    int priority = oper / 100;
    if (priority > 9 || priority < 0) priority = -1;
    return priority;
}

// int oper_priority(char oper) {
//     int priority = -2;
//     switch (oper) {
//         case ')':
//             priority = 0;
//             break;
//         case '(':
//             priority = 1;
//             break;
//         case '+' || '-':
//             priority = 2;
//             break;
//         case '*' || '/':
//             priority = 3;
//             break;
//         case '%':
//             priority = 4;
//             break;
//         case '^':
//             priority = 5;
//         default:
//             priority = -1;  // error
//             break;
//     }

//     return priority;
// }