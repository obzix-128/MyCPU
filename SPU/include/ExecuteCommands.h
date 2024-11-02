#ifndef EXECUTECOMMANDS_H
#define EXECUTECOMMANDS_H

#include "Processor.h"
#include <assert.h>

ErrorNumbers executeCommands(info_array_with_commands_code* executable_code);
StackElem_t* getArguments(info_array_with_commands_code* executable_code, StackElem_t registers[],
                    StackElem_t random_access_memory[]);
ErrorNumbers executeCurrentCommand(info_array_with_commands_code* executable_code,
                                   StackElem_t registers[], StackElem_t random_access_memory[],
                                   stack_info* my_stack, stack_info* return_address);

const int _SIZE_OF_RAM = 100;

#endif //EXECUTECOMMANDS_H
