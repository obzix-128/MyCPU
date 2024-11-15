#include "../include/PushAndPop.h"
#include "../include/Verificator.h"
#include "../include/DebugOnMode.h"


ErrorNumbers StackPush(stack_info* my_stack, StackElem_t element_value)
{
    ErrorNumbers check_error = _NO_ERROR;

    STACK_VERIFICATOR;

    _CHECK_HASH_DJB;

    check_error = StackMemory(my_stack);
    if(check_error != _NO_ERROR)
    {
        return check_error;
    }
    _CHECK_HASH_DJB;

    my_stack->data[my_stack->size] = element_value;
    my_stack->size++;

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

ErrorNumbers StackPop(stack_info* my_stack, StackElem_t* element_value)
{
    ErrorNumbers check_error = _NO_ERROR;

    STACK_VERIFICATOR;

    _CHECK_HASH_DJB;

    if(my_stack->size <= 0)
    {
        return _CHECK_FOUND_ERROR;
    }

    my_stack->size--;
    *element_value = my_stack->data[my_stack->size];

    for(int i = 0; i < (int)sizeof(StackElem_t); i++)
    {
        ((char*)(&my_stack->data[my_stack->size]))[i] = 52;
    }

    #ifdef _DEBUG_HASH_DJB
    check_error = calculateHash(my_stack);
    if(check_error != _NO_ERROR)
    {
        return check_error;
    }
    #endif // _DEBUG_HASH_DJB

    check_error = StackMemory(my_stack);
    if(check_error != _NO_ERROR)
    {
        return check_error;
    }
    _CHECK_HASH_DJB;

    STACK_VERIFICATOR;

    return check_error;
}

ErrorNumbers StackMemory(stack_info* my_stack)
{
    ErrorNumbers check_error = _NO_ERROR;

    STACK_VERIFICATOR;

    _CHECK_HASH_DJB;

    int new_size = 0;
    if(my_stack->size < MIN_STACK_SIZE)
    {
        return _NO_ERROR;
    }
    if(my_stack->size == my_stack->capacity)
    {
        new_size = my_stack->capacity * 2;
    }
    if(my_stack->size == my_stack->capacity / 4)
    {
        new_size = my_stack->capacity / 2;
    }
    if(new_size == 0)
    {
        return _NO_ERROR;
    }

    #ifdef _DEBUG_CHICK_CHIRICK
    my_stack->full_data = (StackElem_t*) realloc(my_stack->full_data, new_size * sizeof(StackElem_t) +
                                                                    SIZE_CHICK_CHIRICK * 2);
    if(my_stack->full_data == NULL)
    {
        return _CALLOC_ERROR;
    }
    my_stack->data = (StackElem_t*)((char*)my_stack->full_data + SIZE_CHICK_CHIRICK);
    #else
    my_stack->data = (StackElem_t*) realloc(my_stack->data, new_size * sizeof(StackElem_t));
    if(my_stack->data == NULL)
    {
        return _CALLOC_ERROR;
    }
    #endif // _DEBUG_CHICK_CHIRICK

    memset(&(my_stack->data[my_stack->size]), 52, my_stack->size * (int)sizeof(StackElem_t));

    my_stack->capacity = new_size;

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
