#ifndef COMMANDS_H
#define COMMANDS_H

#include "Processor.h"

#include <math.h>

ErrorNumbers pushCommand(info_array_with_commands_code* executable_code, StackElem_t registers[],
                         StackElem_t random_access_memory[], stack_info* my_stack);
ErrorNumbers popCommand(info_array_with_commands_code* executable_code, StackElem_t registers[],
                        StackElem_t random_access_memory[], stack_info* my_stack);
ErrorNumbers outCommand(info_array_with_commands_code* executable_code, stack_info* my_stack);
ErrorNumbers dumpCommand(info_array_with_commands_code* executable_code, stack_info* my_stack);
ErrorNumbers hltCommand(info_array_with_commands_code* executable_code);
ErrorNumbers inCommand(info_array_with_commands_code* executable_code, stack_info* my_stack);
ErrorNumbers addCommand(info_array_with_commands_code* executable_code, stack_info* my_stack);
ErrorNumbers subCommand(info_array_with_commands_code* executable_code, stack_info* my_stack);
ErrorNumbers mulCommand(info_array_with_commands_code* executable_code, stack_info* my_stack);
ErrorNumbers divCommand(info_array_with_commands_code* executable_code, stack_info* my_stack);
ErrorNumbers sqrtCommand(info_array_with_commands_code* executable_code, stack_info* my_stack);
ErrorNumbers sinCommand(info_array_with_commands_code* executable_code, stack_info* my_stack);
ErrorNumbers cosCommand(info_array_with_commands_code* executable_code, stack_info* my_stack);
ErrorNumbers jmpCommand(info_array_with_commands_code* executable_code);
ErrorNumbers jbCommand(info_array_with_commands_code* executable_code, stack_info* my_stack);
ErrorNumbers callCommand(info_array_with_commands_code* executable_code, stack_info* return_address);
ErrorNumbers retCommand(info_array_with_commands_code* executable_code, stack_info* return_address);
ErrorNumbers prntCommand(info_array_with_commands_code* executable_code,
                         StackElem_t random_access_memory[]);
ErrorNumbers jeCommand(info_array_with_commands_code* executable_code, stack_info* my_stack);
ErrorNumbers sqrCommand(info_array_with_commands_code* executable_code, stack_info* my_stack);

#endif // COMMANDS_H
