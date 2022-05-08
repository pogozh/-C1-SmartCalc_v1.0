#include "pars.h"
// PARSER
bool pars_lexeme(char* str, lex* retlex, int* retLen, bool unarop) {
    bool parsed = false;
    int parsChr = FAILD;
    if (retlex != NULL) {
        retlex->num = 0;
        retlex->chr = '\0';
        retlex->type = UNDEFINED;

        if ((parsChr = parse_funx(str, retLen)) != FAILD) {
            retlex->type = FUNCTION;
            retlex->chr = parsChr;
            parsed = true;
        } else if ((parsChr = parse_bracket(str)) != FAILD) {
            *retLen = 1;
            retlex->type = BRACKET;
            retlex->chr = parsChr;
            parsed = true;
        } else {
            double num;
            char chr;
            int opLen;
            parsChr = parse_op(str, &opLen);
            parse_num(str, retLen, &num, &chr);
            if (parsChr != FAILD) {
                if (strchr("+-", parsChr) != NULL && unarop && *retLen > 0) {
                    retlex->type = NUMBER;
                    retlex->num = num;
                    retlex->chr = parsChr;
                    parsed = true;
                } else {
                    retlex->type = OPERATOR;
                    retlex->chr = parsChr;
                    *retLen = opLen;
                    parsed = true;
                }
            }
        }

        if (parsed == false) {
            double num;
            char chr;
            parse_num(str, retLen, &num, &chr);
            if (*retLen > 0) {
                retlex->type = NUMBER;
                retlex->num = num;
                retlex->chr = chr;
                parsed = true;
            }
        }
    }
    return parsed;
}

char parse_funx(char* str, int* len) {
    char ret = FAILD;

    if (strstr(str, "cos") == str || strstr(str, "sin") == str ||
        strstr(str, "tan") == str || strstr(str, "ln") == str) {
        *len = 3;
        ret = str[0];
        if (ret == 'l') *len = 2;
    }
    if ((ret == FAILD) &&
        (strstr(str, "acos") == str || strstr(str, "asin") == str ||
         strstr(str, "atan") == str || strstr(str, "sqrt") == str)) {
        *len = 4;
        ret = str[1];
        if (str[1] != 'q') ret -= 32;
    }
    if ((ret == FAILD) && strstr(str, "log") == str) {
        *len = 3;
        ret = 'L';
    }
    return ret;
}

char parse_bracket(char* str) {
    char ret = FAILD;
    if (strstr(str, "(") == str)
        ret = '(';
    else if (strstr(str, ")") == str)
        ret = ')';
    return ret;
}

char parse_op(char* str, int* len) {
    char ret = FAILD;
    if (strstr(str, "+") == str)
        ret = '+';
    else if (strstr(str, "-") == str)
        ret = '-';
    else if (strstr(str, "*") == str)
        ret = '*';
    else if (strstr(str, "/") == str)
        ret = '/';
    else if (strstr(str, "^") == str)
        ret = '^';
    else if (strstr(str, "mod") == str)
        ret = 'm';

    if (ret != FAILD) *len = 1;
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
bool str_to_polish(char* string, que** retqueue) {
    int status = true;
    stack_t* tempst = stack_init();
    *retqueue = queue_init();
    char *str = NULL, *origstr = NULL;
    if ((status = (string != NULL))) {
        int len = strlen(string);
        str = (char*)calloc(sizeof(char), len + 10);
        origstr = str;
        snprintf(str, len + 9, "%s", string);
        rm_spaces(str);
        if (strlen(str) <= 0) status = false;
    }

    int unary = true;
    lex prevlex, curlex;
    prevlex.type = UNDEFINED;
    while (status && *str != '\0') {
        int curlen = 0;
        if (validate(curlex, prevlex) &&
            pars_lexeme(str, &curlex, &curlen, unary)) {
            unary = (curlex.type == OPERATOR || curlex.chr == '(');
            str += curlen;

            // SORT STATION START

            // 1. if current char is number -> add lexeme to output queue
            if (curlex.type == NUMBER) queue_add_new_lex(*retqueue, curlex);
            // 2. if current char is function -> add lexeme to stack
            if (curlex.type == FUNCTION || curlex.chr == '(')
                stack_add_new_lex(tempst, curlex);
            // 3. if current char is operator
            if (curlex.type == OPERATOR) {
                while (tempst->size > 0 &&
                       op_prior_cmp(curlex.chr, tempst->head->lexi->chr) &&
                       (tempst->head->lexi->type == FUNCTION ||
                        tempst->head->lexi->type == OPERATOR))
                    queue_push(*retqueue, stack_pop(tempst, 0));

                stack_add_new_lex(tempst, curlex);
            }
            // 4. if current cher = )
            if (curlex.chr == ')') {
                if (tempst->size <= 0) {
                    status = false;
                    break;
                } else {
                    // put from stack to queue untill find '(' in stack
                    while (tempst->head->lexi->chr != '(') {
                        queue_push(*retqueue, stack_pop(tempst, 0));
                        if (tempst->size <= 0) {
                            status = false;
                            break;
                        }
                    }
                    if (status == true) {
                        stack_pop(tempst, 1);
                        if (tempst->size > 0 &&
                            tempst->head->lexi->type == FUNCTION)
                            queue_push(*retqueue, stack_pop(tempst, 0));
                    }
                }
            }

            // END OF SORT STATION

            prevlex.chr = curlex.chr;
            prevlex.num = curlex.num;
            prevlex.type = curlex.type;
        } else {
            status = false;
            printf("\n ERROR SORT STATION \n");
            break;
        }
    }

    if (curlex.type != NUMBER && curlex.chr != ')') status = false;
    while (tempst->size > 0) queue_push(*retqueue, stack_pop(tempnam, 0));

    // free struckts
    if (origstr != NULL) free(origstr);
    stack_free(tempst);
    return status;
}

bool validate(lex curl, lex prevl) {
    bool retval = true;
    switch (prevl.type) {
        case NUMBER:
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
        if (op1 == '^') retval = false;  // right-accociative operator
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
