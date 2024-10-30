#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "../../GeneralDirectory/include/GeneralInclude.h"
#include "MyStack.h"

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

#endif // ASSEMBLER_H
