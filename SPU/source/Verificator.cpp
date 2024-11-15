#include "../include/Verificator.h"
#include "../include/Dump.h"


ErrorNumbers StackVerificator(stack_info* my_stack)
{
    if(my_stack == NULL)
    {
        StackDump(my_stack);
        return _NULL_ADDRESS_ERROR;
    }
    if(my_stack->data == NULL)
    {
        StackDump(my_stack);
        return _NULL_ADDRESS_ERROR;
    }
    if(my_stack->size < 0)
    {
        StackDump(my_stack);
        return _CHECK_FOUND_ERROR;
    }
    if(my_stack->capacity < MIN_STACK_SIZE)
    {
        StackDump(my_stack);
        return _CHECK_FOUND_ERROR;
    }
    if(my_stack->size > my_stack->capacity)
    {
        StackDump(my_stack);
        return _CHECK_FOUND_ERROR;
    }

    #ifdef _DEBUG_CHICK_CHIRICK
    int* chick_chirick_in_struct_one = (int*)&(my_stack->chick_chirick_one);
    int* chick_chirick_in_struct_two = (int*)&(my_stack->chick_chirick_two);

    int* chick_chirick_before_stack = (int*)my_stack->full_data;
    int* chick_chirick_after_stack  = (int*)(((char*)my_stack->full_data) +
         SIZE_CHICK_CHIRICK + my_stack->capacity * (int)sizeof(StackElem_t) +
         (8 - my_stack->capacity * (int)sizeof(StackElem_t)) % 8);

    for(int i = 0; i < SIZE_CHICK_CHIRICK / (int)sizeof(int); i++)
    {
        if(chick_chirick_in_struct_one[i] != BAD_BEDA ||
           chick_chirick_in_struct_two[i] != BAD_BEDA ||
           chick_chirick_before_stack [i] != BAD_BEDA ||
           chick_chirick_after_stack  [i] != BAD_BEDA)
        {
            StackDump(my_stack);
            return _CHECK_FOUND_ERROR;
        }
    }
    #endif // _DEBUG_CHICK_CHIRICK

    return _NO_ERROR;
}
