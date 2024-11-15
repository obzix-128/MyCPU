#include "../include/Dump.h"


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
