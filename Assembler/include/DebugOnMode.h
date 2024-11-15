#ifndef DEBUGONMODE_H
#define DEBUGONMODE_H

#include "../include/MyStack.h"

#ifdef _DEBUG_HASH_DJB
ErrorNumbers calculateHash(stack_info* my_stack);
#endif // _DEBUG_HASH_DJB
#ifdef _DEBUG_CHICK_CHIRICK
ErrorNumbers StackChickChiric(stack_info* my_stack);
#endif // _DEBUG_CHICK_CHIRICK

#endif // DEBUGONMODE_H
