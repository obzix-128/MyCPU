#ifndef PUSHANDPOP_H
#define PUSHANDPOP_H

#include "../include/MyStack.h"

#include <stdlib.h>

ErrorNumbers StackPush(stack_info* my_stack, StackElem_t element_value);
ErrorNumbers StackPop (stack_info* my_stack, StackElem_t* element_value);

ErrorNumbers StackMemory(stack_info* my_stack);

#endif // PUSHANDPOP_H
