#include "../include/MyStack.h"


ErrorNumbers StackCtor(stack_info* my_stack)
{
    if(my_stack == NULL)
    {
        printf("Broken address my_stack\n");
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

    my_stack = NULL;

    return _NO_ERROR;
}

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
        return _NULL_ADDRESS_ERROR;
    }
    if(my_stack->full_data == NULL)
    {
        return _NULL_ADDRESS_ERROR;
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

ErrorNumbers StackDump(stack_info* my_stack)
{
    FILE* file_address = fopen("DumpOutput.txt", "w");
    if(file_address == NULL)
    {
        return _OPEN_ERROR;
    }

    if(my_stack != NULL)
    {
        fprintf(file_address,
                "my_stack address[%p]\n",
                my_stack);
    }
    else
    {
        fprintf(file_address,
                "Broken address my_stack\n");
        return _NULL_ADDRESS_ERROR;
    }

    #ifdef _DEBUG_CHICK_CHIRICK
    int* chick_chirick_in_struct_one = (int*)&(my_stack->chick_chirick_one);
    for(int i = 0; i < SIZE_CHICK_CHIRICK / (int)sizeof(int); i++)
    {
        fprintf(file_address,
                "chick_chirick[%d] = <%x>, chick_chirick address = [%p]\n",
                i, chick_chirick_in_struct_one[i], &chick_chirick_in_struct_one[i]);
    }

    if(my_stack->full_data != NULL)
    {
        fprintf(file_address,
                "my_stack->full_data address = [%p]\n",
                my_stack->full_data);
    }
    else
    {
        fprintf(file_address,
                "Broken address my_stack->full_data\n");
    }
    #define _ " "
    #else
    #define _
    #endif // _DEBUG_CHICK_CHIRICK

    if(my_stack->data != NULL)
    {
        fprintf(file_address,
                "my_stack->data" _ "address = [%p]\n",
                my_stack->data);
    }
    else
    {
        fprintf(file_address,
                "Broken address my_stack->data\n");
    }

    fprintf(file_address,
            "my_stack->size     " _ "address = [%p], size     value = <%4.d>\n"
            "my_stack->capacity " _ "address = [%p], capacity value = <%4.d>\n",
            &my_stack->size,     my_stack->size,
            &my_stack->capacity, my_stack->capacity);

    #ifdef _DEBUG_HASH_DJB
    fprintf(file_address,
            "my_stack->hash_djb = %lld\n", // PRI64
            my_stack->hash_djb);
    #endif // _DEBUG_HASH_DJB

    #ifdef _DEBUG_CHICK_CHIRICK
    int* chick_chirick_in_struct_two = (int*)&(my_stack->chick_chirick_two);
    for(int i = 0; i < SIZE_CHICK_CHIRICK / (int)sizeof(int); i++)
    {
        fprintf(file_address,
                "chick_chirick[%d] = <%x>, chick_chirick address = [%p]\n",
                i, chick_chirick_in_struct_two[i], &chick_chirick_in_struct_two[i]);
    }
    #endif // _DEBUG_CHICK_CHIRICK

    fprintf(file_address,
            "\nStack Contents:\n{\n");

    #ifdef _DEBUG_CHICK_CHIRICK
    int* chick_chirick_before_stack = (int*)my_stack->full_data;
    for(int i = 0; i < SIZE_CHICK_CHIRICK / (int)sizeof(int); i++)
    {
        fprintf(file_address,
                "chick_chirick[%d] = <%x>, chick_chirick address = [%p]\n",
                i, chick_chirick_before_stack[i], &chick_chirick_before_stack[i]);
    }
    #endif // _DEBUG_CHICK_CHIRICK

    if(my_stack->data != NULL)
    {
        for(int i = 0; i < my_stack->capacity; i++)
        {
            fprintf(file_address,
                    "size = (%4.d), element value = <" STACK_ELEM_T ">, element address = [%p]\n",
                    i, my_stack->data[i], &my_stack->data[i]);
        }
    }

    #ifdef _DEBUG_CHICK_CHIRICK
    int* chick_chirick_after_stack  = (int*)(((char*)my_stack->full_data) +
         SIZE_CHICK_CHIRICK + my_stack->capacity * (int)sizeof(StackElem_t) +
         (8 - my_stack->capacity * (int)sizeof(StackElem_t)) % 8);
    for(int i = 0; i < SIZE_CHICK_CHIRICK / (int)sizeof(int); i++)
    {
        fprintf(file_address,
                "chick_chirick[%d] = <%x>, chick_chirick address = [%p]\n",
                i, chick_chirick_after_stack[i], &chick_chirick_after_stack[i]);
    }
    #endif // _DEBUG_CHICK_CHIRICK

    fprintf(file_address,
            "}\n");

    fclose(file_address);

    #undef  _

    return _NO_ERROR;
}

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
