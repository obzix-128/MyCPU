#ifndef MYSTACK_H
#define MYSTACK_H

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#include "../../GeneralDirectory/include/GeneralInclude.h"

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

typedef int StackElem_t;

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

ErrorNumbers StackCtor(stack_info* my_stack);
ErrorNumbers StackDtor(stack_info* my_stack);

#ifdef _DEBUG_HASH_DJB
ErrorNumbers calculateHash(stack_info* my_stack);
#endif // _DEBUG_HASH_DJB
#ifdef _DEBUG_CHICK_CHIRICK
ErrorNumbers StackChickChiric(stack_info* my_stack);
#endif // _DEBUG_CHICK_CHIRICK

ErrorNumbers StackDump(stack_info* my_stack);
#define STACK_ELEM_T "%d"

ErrorNumbers StackPush(stack_info* my_stack, StackElem_t element_value);
ErrorNumbers StackPop (stack_info* my_stack, StackElem_t* element_value);

ErrorNumbers StackMemory(stack_info* my_stack);

ErrorNumbers StackVerificator(stack_info* my_stack);

#define STACK_VERIFICATOR if(StackVerificator(my_stack)) return StackVerificator(my_stack);

const int INT_MULTIPLIER = 100;

#endif // MYSTACK_H
