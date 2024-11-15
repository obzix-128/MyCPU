#include "../include/DebugOnMode.h"
#include "../include/Verificator.h"


#ifdef _DEBUG_HASH_DJB
// https://github.com/dim13/djb2/blob/master/docs/hash.md - explanation of the hash function
ErrorNumbers calculateHash(stack_info* my_stack)
{
    STACK_VERIFICATOR; // Эту вырежу

    my_stack->hash_djb = 5381;

    for(int i = 0; i < (int)sizeof(my_stack) - (int)sizeof(my_stack->hash_djb) - SIZE_CHICK_CHIRICK * 2;
                i++)
    {
        my_stack->hash_djb = my_stack->hash_djb * 31 + (int)*(((char*)my_stack) + SIZE_CHICK_CHIRICK + i);
    }

    for(int i = 0; i < (int)sizeof(my_stack->capacity); i++)
    {
        my_stack->hash_djb = my_stack->hash_djb * 31 + (int)*(((char*)my_stack->data) + i);
    }

    STACK_VERIFICATOR;
    return _NO_ERROR;
}
#endif // _DEBUG_HASH_DJB

#ifdef _DEBUG_CHICK_CHIRICK
ErrorNumbers StackChickChiric(stack_info* my_stack)
{
    if(my_stack == NULL)
    {
        return NULL_ADDRESS_ERROR;
    }
    if(my_stack->full_data == NULL)
    {
        return NULL_ADDRESS_ERROR;
    }

    int* chick_chirick_in_struct_one = (int*)&(my_stack->chick_chirick_one);
    int* chick_chirick_in_struct_two = (int*)&(my_stack->chick_chirick_two);

    int* chick_chirick_before_stack = (int*)my_stack->full_data;
    int* chick_chirick_after_stack  = (int*)(((char*)my_stack->full_data) +
         SIZE_CHICK_CHIRICK + my_stack->capacity * (int)sizeof(StackElem_t) +
         (8 - my_stack->capacity * (int)sizeof(StackElem_t)) % 8);

    for(int i = 0; i < SIZE_CHICK_CHIRICK / (int)sizeof(int); i++)
    {
        chick_chirick_in_struct_one[i] = BAD_BEDA;
        chick_chirick_in_struct_two[i] = BAD_BEDA;
        chick_chirick_before_stack [i] = BAD_BEDA;
        chick_chirick_after_stack  [i] = BAD_BEDA;
    }

    STACK_VERIFICATOR;

    return _NO_ERROR;
}
#endif // _DEBUG_CHICK_CHIRICK
