#include "calc.h"

#include "pars.h"

// int main() {
//     // test stack 01
//     stack_t s = create_stack();
//     // push(s, 111);
//     stack_print(&s);
//     for (int i = 0; i < 5; i++) {
//         push(&s, i);
//         stack_print(&s);
//     }
//     printf("!peek top = %f\n", stack_peek(&s));
//     for (int i = 0; i < 5; i++) {
//         stack_print(&s);
//         pop(&s);
//     }
//     pop(&s);
//     stack_delete(&s);

// // parser test 01
// stack_t oper = create_stack();
// // push(s, 111);
// stack_print(&oper);
// for (int i = 0; i < 10; i++) {
//     push(&oper, i * 100);
//     stack_print(&oper);
// }
// printf("!peek top = %f\n", stack_peek(&oper));
// for (int i = 0; i < 10; i++) {
//     printf("%d ", oper_priority(oper));
//     pop(&oper);
// }
// stack_delete(&oper);
//     return 0;
// }
