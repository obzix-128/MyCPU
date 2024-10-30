#include "../include/TextHandler.h"


ErrorNumbers checkVersion(info_array_with_commands_txt* commands)
{
    unsigned int command_size = 0;
    const unsigned int SIGNATURE_SIZE = 11;
    char signature[SIGNATURE_SIZE] = {};

    sscanf(commands->array, "%s%n", signature, &command_size);
    if(strcmp(signature, _SIGNATURE_) != 0)
    {
        return _SIGNATURE_ERROR;
    }
    commands->array = commands->array + command_size;
    commands->size_of_array = commands->size_of_array - (command_size + 1);

    sscanf(commands->array, "%s%n", signature, &command_size);
    if(strcmp(signature, _ASSEMBLER_VERSION_) != 0)
    {
        return _SIGNATURE_ERROR;
    }
    commands->array = commands->array + command_size + 1;
    commands->size_of_array = commands->size_of_array - (command_size + 1);

    return _NO_ERROR;
}

ErrorNumbers processingAnArrayOfCommands(info_array_with_commands_txt* commands,
                                         info_array_with_commands_code* executable_code)
{
    unsigned int commands_were_read = 0;
    unsigned int command_size = 0;

    executable_code->code = (int*) calloc(_SIZE_OF_THE_ARRAY_WITH_COMMANDS, sizeof(int));

    for(int i = 0; commands_were_read < commands->size_of_array; i++)
    {
        sscanf(commands->array + commands_were_read, "%x%n", &(executable_code->code[i]), &command_size);
        commands_were_read += command_size;
        executable_code->size_of_code++;
    }

    return _NO_ERROR;
}
