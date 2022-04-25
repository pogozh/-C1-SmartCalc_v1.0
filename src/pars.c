#include "pars.h"

int oper_priority(stack_t oper) {
    int priority = (int)oper.data[oper.top] / 100;
    if (priority > 9 || priority < 0) priority = -1;

    return priority;
}
