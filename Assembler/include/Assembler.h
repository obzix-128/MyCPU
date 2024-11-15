#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "../../GeneralDirectory/include/GeneralInclude.h"
#include "MyStack.h"
#include "CtorAndDtor.h"
#include "Dump.h"
#include "PushAndPop.h"
#include "Verificator.h"
#include "ErrorHandler.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct info_array_with_verbal_commands {
    char* array_with_verbal_commands;
    unsigned int size_of_the_array_with_verbal_commands;
};

struct info_array_with_commands {
    int* array_with_commands;
    unsigned int size_of_array_with_commands;
    unsigned int number_of_commands;
};

#define CHECK_ERROR(func) check_error = func; if(check_error != _NO_ERROR) \
                                                  {errorHandler(check_error); return check_error;}
#define CHECK_NULL_ADDR_ERROR(variable, ERROR_NUMBER) if(variable == NULL) \
                                     {return ERROR_NUMBER;}

#endif // ASSEMBLER_H
