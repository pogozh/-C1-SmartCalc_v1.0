#include "pars.h"

int oper_priority(stack_t oper) {
    int priority = (int)oper.data[oper.top] / 100;
    if (priority > 9 || priority < 0) priority = -1;

    return priority;
}

// void testp() {
//     double result;
//     char *elem;
//     int sizeArg, unar, countNum, flag = 0;
//     elem = (char *)malloc(sizeArg * sizeof(char));
//     for (int i = 1; i < argc; i++) {
//         strcpy(elem, argv[i]);
//     }
//     result = mainFunc(elem);
//     free(elem);
//     printf("%lf", result);
// }
