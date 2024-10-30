#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "../../GeneralDirectory/include/GeneralInclude.h"
#include "MyStack.h"

struct info_array_with_commands_txt {
    char* array;
    unsigned int size_of_array;
};

struct info_array_with_commands_code {
    int* code;
    unsigned int ip;
    unsigned int size_of_code;
};

#endif // PROCESSOR_H
