#include "../include/Commands.h"


ErrorNumbers pushOrPop(info_array_with_commands* array_nl_cmd,
                       info_array_with_verbal_commands* array_vb_cmd, CommandNumber PUSH_OR_POP,
                       unsigned int* characters_were_read, unsigned int* ip, char* command)
{
    CHECK_NULL_ADDR_ERROR(array_nl_cmd, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(array_vb_cmd, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(characters_were_read, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(ip, _NULL_ADDRESS_ERROR);

    unsigned int command_size = 0;

    array_nl_cmd->array_with_commands[*ip] =
    array_nl_cmd->array_with_commands[*ip] | PUSH_OR_POP;

    sscanf(array_vb_cmd->array_with_verbal_commands + (*characters_were_read), "%s%n",
            command, (int*)&command_size);

    *characters_were_read += command_size + 1;

    char* pointer = NULL;

    if(strchr(command, 'x') && strchr(command, '+') && strchr(command, '['))
    {
        array_nl_cmd->array_with_commands[*ip] =
        array_nl_cmd->array_with_commands[*ip] | TURN_ON_IMMED | TURN_ON_REGISTERS | TURN_ON_RAM;

        pointer = strchr(command, '+');
        sscanf(pointer, "+%d", &array_nl_cmd->array_with_commands[*ip + 1]);

        pointer = strchr(command, 'x');
        array_nl_cmd->array_with_commands[*ip + 2] = ((*(pointer - 1) - 'a') + 1);
        if(array_nl_cmd->array_with_commands[*ip + 2] > (signed int)_NUMBER_OF_REGISTERS)
        {
            return _REGISTER_LIM_ERROR;
        }

        *ip += 1;
    }
    else if(strchr(command, 'x') &&  strchr(command, '['))
    {
        array_nl_cmd->array_with_commands[*ip] =
        array_nl_cmd->array_with_commands[*ip] | TURN_ON_REGISTERS | TURN_ON_RAM;

        pointer = strchr(command, 'x');
        array_nl_cmd->array_with_commands[*ip + 1] = ((*(pointer - 1) - 'a') + 1);
        if(array_nl_cmd->array_with_commands[*ip + 1] > (signed int)_NUMBER_OF_REGISTERS)
        {
            return _REGISTER_LIM_ERROR;
        }
    }
    else if(strchr(command, '['))
    {
        array_nl_cmd->array_with_commands[*ip] =
        array_nl_cmd->array_with_commands[*ip] | TURN_ON_IMMED | TURN_ON_RAM;

        pointer = strchr(command, '[');
        sscanf(pointer, "[%d", &array_nl_cmd->array_with_commands[*ip + 1]);
    }
    else if(strchr(command, '+'))
    {
        array_nl_cmd->array_with_commands[*ip] =
        array_nl_cmd->array_with_commands[*ip] | TURN_ON_IMMED | TURN_ON_REGISTERS;

        pointer = strchr(command, '+');
        sscanf(pointer, "+%d", &array_nl_cmd->array_with_commands[*ip + 1]);

        pointer = strchr(command, 'x');
        array_nl_cmd->array_with_commands[*ip + 2] = ((*(pointer - 1) - 'a') + 1);
        if(array_nl_cmd->array_with_commands[*ip + 2] > (signed int)_NUMBER_OF_REGISTERS)
        {
            return _REGISTER_LIM_ERROR;
        }

        *ip += 1;
    }
    else if(strchr(command, 'x'))
    {
        array_nl_cmd->array_with_commands[*ip] =
        array_nl_cmd->array_with_commands[*ip] | TURN_ON_REGISTERS;

        pointer = strchr(command, 'x');
        array_nl_cmd->array_with_commands[*ip + 1] = ((*(pointer - 1) - 'a') + 1);
        if(array_nl_cmd->array_with_commands[*ip + 1] > (signed int)_NUMBER_OF_REGISTERS)
        {
            return _REGISTER_LIM_ERROR;
        }
    }
    else
    {
        array_nl_cmd->array_with_commands[*ip] =
        array_nl_cmd->array_with_commands[*ip] | TURN_ON_IMMED;

        sscanf(command, "%d", &array_nl_cmd->array_with_commands[*ip + 1]);
    }

    *ip += 2;

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
