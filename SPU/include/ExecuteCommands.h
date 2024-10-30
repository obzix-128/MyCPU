#ifndef EXECUTECOMMANDS_H
#define EXECUTECOMMANDS_H

#include "Processor.h"
#include <assert.h>
#include <math.h>

ErrorNumbers executeCommands(info_array_with_commands_code* executable_code);
StackElem_t* getArguments(info_array_with_commands_code* executable_code, StackElem_t registers[],
                    StackElem_t random_access_memory[]);

const int _SIZE_OF_RAM = 100;

#endif //EXECUTECOMMANDS_H
