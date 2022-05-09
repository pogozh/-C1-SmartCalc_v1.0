#include "calc.h"

double calculate(que* exp, double x) {
    double result = 0.0;
    quEl* curel = exp->tail;
    mstack* stack = stack_init();

    while (curel != NULL) {
        lex* curlex = curel->lexi;
        curel = curel->next;

        // if current lexeme is number
        if (curlex->type == NUMBER) {
            lex* lexnum = (lex*)calloc(1, sizeof(lex));
            lexnum->type = NUMBER;
            if (curlex->chr != 'x') {
                lexnum->num = curlex->num;
            } else {
                lexnum->num = x;
                if (curlex->num < 0) lexnum->num *= -1;
            }
            stack_push(stack, lexnum);
        }
        // if is function
        if (curlex->type == FUNCTION) {
            lex* stackVal = stack_pop(stack);
            if (stackVal->type != NUMBER)
                printf("\n!ERR:stack->num is NOT a num\n");
            double res_value = calc_fux(stackVal->num, curlex->chr);
            stackVal->num = res_value;
            stack_push(stack, stackVal);
        }
        // if is operator
        if (curlex->type == OPERATOR) {
            lex* num1 = stack_pop(stack);
            lex* num2 = stack_pop(stack);
            if (num1->type != NUMBER) printf("\n!ERR:num1 is NOT a num");
            if (num2->type != NUMBER) printf("\n!ERR:num2 is NOT a num");
            double res_value = calc_nums(num1->num, num2->num, curlex->chr);
            free(num1);
            free(num2);
            lex* lexnum = (lex*)calloc(1, sizeof(lex));
            lexnum->num = res_value;
            lexnum->type = NUMBER;
            stack_push(stack, lexnum);
        }
    }

    lex* stackResult = stack_pop(stack);
    if (stackResult->type != NUMBER) printf("\n!ERR:result is NOT a num\n");
    result = stackResult->num;
    free(stackResult);
    stack_free(stack);
    return result;
}

double calc_nums(double num1, double num2, char op) {
    double retval;
    switch (op) {
        case '+':
            retval = num2 + num1;
            break;
        case '-':
            retval = num2 - num1;
            break;
        case '*':
            retval = num2 * num1;
            break;

        case '/':
            retval = num2 / num1;
            break;
        case '^':
            retval = pow(num2, num1);
            break;
        case MODE:
            retval = fmod(num2, num1);
            break;
        default:
            printf("\n!ERR:UNKNOWN OPERATOR '%c'\n", op);
            break;
    }
    return retval;
}

double calc_fux(double value, char op) {
    double retval;
    switch (op) {
        case COS:
            retval = cos(value);
            break;
        case SIN:
            retval = sin(value);
            break;
        case TAN:
            retval = tan(value);
            break;
        case ACOS:
            retval = acos(value);
            break;
        case ASIN:
            retval = asin(value);
            break;
        case ATAN:
            retval = atan(value);
            break;
        case SQRT:
            retval = sqrt(value);
            break;
        case LN:
            retval = log(value);
            break;
        case LOG:
            retval = log10(value);
            break;
        default:
            printf("\n!ERR:UNKNOWN FUNCTION '%c'\n", op);
            break;
    }
    return retval;
}
