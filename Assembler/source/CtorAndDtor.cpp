#include "../include/CtorAndDtor.h"
#include "../include/DebugOnMode.h"
#include "../include/Verificator.h"


ErrorNumbers StackCtor(stack_info* my_stack)
{
    if(my_stack == NULL)
    {
        printf("Broken address my_stack\n"); // TODO: В версии для взлома вырежу
        return _NULL_ADDRESS_ERROR;
    }

    #ifdef _DEBUG_CHICK_CHIRICK
    my_stack->full_data = (StackElem_t*) calloc(1, MIN_STACK_SIZE * sizeof(StackElem_t) +
                                                  SIZE_CHICK_CHIRICK * 2);
    if(my_stack->full_data == NULL)
    {
        return _CALLOC_ERROR;
    }
    my_stack->data = (StackElem_t*)((char*)my_stack->full_data + SIZE_CHICK_CHIRICK);
    #else
    my_stack->data = (StackElem_t*) calloc(MIN_STACK_SIZE, sizeof(StackElem_t));
    if(my_stack->data == NULL)
    {
        return _CALLOC_ERROR;
    }
    #endif // _DEBUG_CHICK_CHIRICK

    my_stack->size = 0;
    my_stack->capacity = MIN_STACK_SIZE;

    const char POISON_VALUE = 52;
    for(int i = 0; i < my_stack->capacity * (int)sizeof(StackElem_t); i++)
    {
        ((char*)(&my_stack->data[my_stack->size]))[i] = POISON_VALUE;
    }

    ErrorNumbers check_error = _NO_ERROR;

    #ifdef _DEBUG_CHICK_CHIRICK
    check_error = StackChickChiric(my_stack);
    if(check_error != _NO_ERROR)
    {
        return check_error;
    }
    #endif // _DEBUG_CHICK_CHIRICK

    #ifdef _DEBUG_HASH_DJB
    check_error = calculateHash(my_stack);
    if(check_error != _NO_ERROR)
    {
        return check_error;
    }
    #endif // _DEBUG_HASH_DJB

    STACK_VERIFICATOR;

    return check_error;
}

ErrorNumbers StackDtor(stack_info* my_stack)
{
    STACK_VERIFICATOR;

    #ifdef _DEBUG_CHICK_CHIRICK
    free(my_stack->full_data);
    #else
    free(my_stack->data);
    #endif // _DEBUG_CHICK_CHIRICK

    *my_stack = {};

    return _NO_ERROR;
}
