#ifndef MYSTACK_H
#define MYSTACK_H

#include "../../GeneralDirectory/include/GeneralInclude.h"

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef _DEBUG_
#define _DEBUG_CHICK_CHIRICK
#define _DEBUG_HASH_DJB
#endif // _DEBUG_

#ifdef _DEBUG_HASH_DJB
#define _CHECK_HASH_DJB do \
                        { \
                        int64_t check_hash_djb = my_stack->hash_djb; \
                        check_error = calculateHash(my_stack); \
                        if(check_error != NO_ERROR) \
                        { \
                            return check_error; \
                        } \
                        if(check_hash_djb != my_stack->hash_djb) \
                        { \
                            return HASH_ERROR; \
                        } \
                        } while(0);
#else
#define _CHECK_HASH_DJB
#endif // _DEBUG_HASH_DJB

#ifdef _DEBUG_CHICK_CHIRICK
#define SIZE_CHICK_CHIRICK 8
#define BAD_BEDA 195935962
#else
#define SIZE_CHICK_CHIRICK 0
#endif // _DEBUG_CHICK_CHIRICK

typedef labels_info StackElem_t;

enum ErrorNumber{
    NO_ERROR           = 0,
    CALLOC_ERROR       = 1,
    CHECK_FOUND_ERROR  = 2,
    OPEN_ERROR         = 3,
    HASH_ERROR         = 4,
    POP_ERROR          = 5,
    NULL_ADDRESS_ERROR = 6
};

struct stack_info{
    #ifdef _DEBUG_CHICK_CHIRICK
    char chick_chirick_one[SIZE_CHICK_CHIRICK];
    StackElem_t* full_data;
    #endif // _DEBUG_CHICK_CHIRICK

    StackElem_t* data;
    int size;
    int capacity;

    #ifdef _DEBUG_HASH_DJB
    int64_t hash_djb;
    #endif // _DEBUG_HASH_DJB
    #ifdef _DEBUG_CHICK_CHIRICK
    char chick_chirick_two[SIZE_CHICK_CHIRICK];
    #endif // _DEBUG_CHICK_CHIRICK
};

const int MIN_STACK_SIZE = 16;

ErrorNumber StackCtor(stack_info* my_stack);
ErrorNumber StackDtor(stack_info* my_stack);

#ifdef _DEBUG_HASH_DJB
ErrorNumber calculateHash(stack_info* my_stack);
#endif // _DEBUG_HASH_DJB
#ifdef _DEBUG_CHICK_CHIRICK
ErrorNumber StackChickChiric(stack_info* my_stack);
#endif // _DEBUG_CHICK_CHIRICK

ErrorNumber StackDump(stack_info* my_stack);
#define STACK_ELEM_T "%4.d"

ErrorNumber StackPush(stack_info* my_stack, StackElem_t element_value);
ErrorNumber StackPop (stack_info* my_stack, StackElem_t* element_value);

ErrorNumber StackMemory(stack_info* my_stack);

ErrorNumber StackVerificator(stack_info* my_stack);

#define STACK_VERIFICATOR if(StackVerificator(my_stack)) return StackVerificator(my_stack);

#endif // MYSTACK_H
