#ifndef COMMANDS_H
#define COMMANDS_H

#include "Assembler.h"

struct arguments
{
    int command;
    int immed;
    int my_register;
};

ErrorNumbers pushOrPop(info_array_with_commands* array_nl_cmd,
                       info_array_with_verbal_commands* array_vb_cmd, CommandNumber PUSH_OR_POP,
                       unsigned int* characters_were_read, unsigned int* ip, char* command);
ErrorNumbers writeArguments(info_array_with_commands* array_nl_cmd, unsigned int* ip,
                            arguments* command_argiments);
ErrorNumbers checkImmed(arguments* command_argiments, info_array_with_verbal_commands* array_vb_cmd,
                        unsigned int* characters_were_read, char* command);
ErrorNumbers checkRegister(arguments* command_argiments, char* command);
ErrorNumbers checkRandomAccessMemory(arguments* command_argiments, char* command);
ErrorNumbers differentJumpsCommands(info_array_with_commands* array_nl_cmd,
                                    info_array_with_verbal_commands* array_vb_cmd,
                                    CommandNumber COMMAND, unsigned int* characters_were_read,
                                    unsigned int* ip, char* command, char* label_name,
                                    const int NUMBER_OF_LABELS, stack_info* fixup,
                                    labels_info* lables_for_assembler);

#endif // COMMANDS_H
