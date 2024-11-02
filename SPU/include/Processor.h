#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "../../GeneralDirectory/include/GeneralInclude.h"
#include "MyStack.h"
#include "ErrorHandler.h"

struct info_array_with_commands_txt {
    char* array;
    unsigned int size_of_array;
};

struct info_array_with_commands_code {
    int* code;
    unsigned int ip;
    unsigned int size_of_code;
};

#define CHECK_ERROR(func) check_error = func; if(check_error != _NO_ERROR) {errorHandler(check_error); return check_error;}
#define CHECK_NULL_ADDR_ERROR(variable, ERROR_NUMBER) if(variable == NULL) \
                                     {return ERROR_NUMBER;}

#endif // PROCESSOR_H
