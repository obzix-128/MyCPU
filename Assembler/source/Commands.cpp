#include "../include/Commands.h"


ErrorNumbers pushOrPop(info_array_with_commands* array_nl_cmd,
                       info_array_with_verbal_commands* array_vb_cmd, CommandNumber PUSH_OR_POP,
                       unsigned int* characters_were_read, unsigned int* ip, char* command)
{
    CHECK_NULL_ADDR_ERROR(array_nl_cmd, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(array_vb_cmd, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(characters_were_read, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(ip, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    struct arguments command_argiments = {};
    unsigned int command_size = 0;

    command_argiments.command = command_argiments.command | PUSH_OR_POP;

    sscanf(array_vb_cmd->array_with_verbal_commands + (*characters_were_read), "%s%n",
            command, (int*)&command_size);

    CHECK_ERROR(checkImmed(&command_argiments,  array_vb_cmd, characters_were_read, command));
    CHECK_ERROR(checkRegister(&command_argiments, command));
    CHECK_ERROR(checkRandomAccessMemory(&command_argiments, command));

    CHECK_ERROR(writeArguments(array_nl_cmd, ip, &command_argiments));

    *characters_were_read += command_size + 1;

    return check_error;
}

ErrorNumbers writeArguments(info_array_with_commands* array_nl_cmd, unsigned int* ip,
                            arguments* command_argiments)
{
    CHECK_NULL_ADDR_ERROR(array_nl_cmd, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(ip, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(command_argiments, _NULL_ADDRESS_ERROR);

    array_nl_cmd->array_with_commands[*ip] = command_argiments->command;
    *ip += 1;
    if(command_argiments->command & TURN_ON_IMMED)
    {
        array_nl_cmd->array_with_commands[*ip] = command_argiments->immed;
        *ip += 1;
    }
    if(command_argiments->command & TURN_ON_REGISTERS)
    {
        array_nl_cmd->array_with_commands[*ip] = command_argiments->my_register;
        *ip += 1;
    }

    return _NO_ERROR;
}

ErrorNumbers checkImmed(arguments* command_argiments, info_array_with_verbal_commands* array_vb_cmd,
                        unsigned int* characters_were_read, char* command)
{
    CHECK_NULL_ADDR_ERROR(command_argiments, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(array_vb_cmd, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(characters_were_read, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(command, _NULL_ADDRESS_ERROR);

    if(sscanf(array_vb_cmd->array_with_verbal_commands + (*characters_were_read),
                   "%*[^0-9+-]%d", &command_argiments->immed))
    {
        command_argiments->command = command_argiments->command | TURN_ON_IMMED;
    }

    return _NO_ERROR;
}

ErrorNumbers checkRegister(arguments* command_argiments, char* command)
{
    CHECK_NULL_ADDR_ERROR(command_argiments, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(command, _NULL_ADDRESS_ERROR);

    if(strchr(command, 'x'))
    {
        command_argiments->command = command_argiments->command | TURN_ON_REGISTERS;

        char* pointer = strchr(command, 'x');

        command_argiments->my_register = ((*(pointer - 1) - 'a') + 1);
        if(command_argiments->my_register  >= (signed int)_NUMBER_OF_REGISTERS ||
           command_argiments->my_register < 0)
        {
            return _REGISTER_LIM_ERROR;
        }
    }

    return _NO_ERROR;
}

ErrorNumbers checkRandomAccessMemory(arguments* command_argiments, char* command)
{
    CHECK_NULL_ADDR_ERROR(command_argiments, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(command, _NULL_ADDRESS_ERROR);

    if(strchr(command, '['))
    {
        command_argiments->command = command_argiments->command | TURN_ON_RAM;
    }

    return _NO_ERROR;
}

ErrorNumbers differentJumpsCommands(info_array_with_commands* array_nl_cmd,
                                    info_array_with_verbal_commands* array_vb_cmd,
                                    CommandNumber COMMAND, unsigned int* characters_were_read,
                                    unsigned int* ip, char* command, char* label_name,
                                    const int NUMBER_OF_LABELS, stack_info* fixup,
                                    labels_info* lables_for_assembler)
{
    CHECK_NULL_ADDR_ERROR(array_nl_cmd, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(array_vb_cmd, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(characters_were_read, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(ip, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(command, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(label_name, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(fixup, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(lables_for_assembler, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;
    unsigned int command_size = 0;
    StackElem_t fixup_element = {};

    sscanf(array_vb_cmd->array_with_verbal_commands + *characters_were_read, "%s%n", label_name,
            (int*)&command_size);
    *characters_were_read += command_size + 1;

    char* colon_address = NULL;
    colon_address = strchr(label_name, ':');
    if(colon_address == NULL)
    {
        return _SYNTAXIS_ERROR;
    }
    *colon_address = '\0';

    for(int i = 0; i < NUMBER_OF_LABELS; i++)
    {
        if(strcmp(label_name, lables_for_assembler[i].label_name) == 0)
        {
            array_nl_cmd->array_with_commands[*ip] = COMMAND;
            array_nl_cmd->array_with_commands[*ip + 1] = lables_for_assembler[i].label_address;
            break;
        }
    }

    if(array_nl_cmd->array_with_commands[*ip] == 0)
    {
        strcpy(fixup_element.label_name, label_name);
        fixup_element.label_address = *ip + 1;

        CHECK_ERROR(StackPush(fixup, fixup_element));

        array_nl_cmd->array_with_commands[*ip] = COMMAND;
        array_nl_cmd->array_with_commands[*ip + 1] = -1;
    }

    *ip += 2;

    return check_error;
}
