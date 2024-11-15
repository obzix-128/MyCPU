#ifndef VERIFICATOR_H
#define VERIFICATOR_H
#include "../include/MyStack.h"

ErrorNumbers StackVerificator(stack_info* my_stack);

#define STACK_VERIFICATOR if(StackVerificator(my_stack)) return StackVerificator(my_stack);

#endif // VERIFICATOR_H
