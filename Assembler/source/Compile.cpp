#include "../include/Compile.h"


ErrorNumbers assemblingCommands(info_array_with_commands* array_nl_cmd,
                                info_array_with_verbal_commands array_vb_cmd) // TODO: Заменить на *?
{
    CHECK_NULL_ADDR_ERROR(array_nl_cmd, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    unsigned int ip = 0;
    unsigned int characters_were_read = 0;
    unsigned int command_size = 0;

    const unsigned int _SIZE_OF_THE_COMMAND = 50;
    char command[_SIZE_OF_THE_COMMAND] = {};

    const int NUMBER_OF_LABELS = 10;
    labels_info* lables_for_assembler = (labels_info*) calloc(NUMBER_OF_LABELS, sizeof(labels_info));
    CHECK_NULL_ADDR_ERROR(lables_for_assembler, _CALLOC_ERROR);

    const unsigned int _SIZE_OF_THE_LABEL_NAME = 11;
    char label_name[_SIZE_OF_THE_LABEL_NAME] = {};

    stack_info fixup = {};

    CHECK_ERROR(StackCtor(&fixup));

    while(characters_were_read < array_vb_cmd.size_of_the_array_with_verbal_commands)
    {
        if(ip >= array_nl_cmd->size_of_array_with_commands)
        {
            return _COMMAND_LIM_ERROR;
        }

        sscanf(array_vb_cmd.array_with_verbal_commands + characters_were_read, "%s%n", command,
               (int*)&command_size);
        characters_were_read += command_size;

        if(command_size > _SIZE_OF_THE_COMMAND)
        {
            return _SIZE_COMMAND_ERROR;
        }

        if(strcmp(command, "push") == 0)
        {
            CHECK_ERROR(pushOrPop(array_nl_cmd, &array_vb_cmd, PUSH_COMMAND, &characters_were_read,
                                  &ip, command));
        }
        else if(strcmp(command, "pop") == 0)
        {
            CHECK_ERROR(pushOrPop(array_nl_cmd, &array_vb_cmd, POP_COMMAND, &characters_were_read,
                                  &ip, command));
        }
        else if(strcmp(command, "out") == 0)
        {
            array_nl_cmd->array_with_commands[ip] = OUT_COMMAND;
            ip += 1;
        }
        else if(strcmp(command, "dump") == 0)
        {
            array_nl_cmd->array_with_commands[ip] = DUMP_COMMAND;
            ip += 1;
        }
        else if(strcmp(command, "hlt") == 0)
        {
            array_nl_cmd->array_with_commands[ip] = HLT_COMMAND;
            ip += 1;
        }
        else if(strcmp(command, "in") == 0)
        {
            array_nl_cmd->array_with_commands[ip] = IN_COMMAND;
            ip += 1;
        }
        else if(strcmp(command, "add") == 0)
        {
            array_nl_cmd->array_with_commands[ip] = ADD_COMMAND;
            ip += 1;
        }
        else if(strcmp(command, "sub") == 0)
        {
            array_nl_cmd->array_with_commands[ip] = SUB_COMMAND;
            ip += 1;
        }
        else if(strcmp(command, "mul") == 0)
        {
            array_nl_cmd->array_with_commands[ip] = MUL_COMMAND;
            ip += 1;
        }
        else if(strcmp(command, "div") == 0)
        {
            array_nl_cmd->array_with_commands[ip] = DIV_COMMAND;
            ip += 1;
        }
        else if(strcmp(command, "sqrt") == 0)
        {
            array_nl_cmd->array_with_commands[ip] = SQRT_COMMAND;
            ip += 1;
        }
        else if(strcmp(command, "sin") == 0)
        {
            array_nl_cmd->array_with_commands[ip] = SIN_COMMAND;
            ip += 1;
        }
        else if(strcmp(command, "cos") == 0)
        {
            array_nl_cmd->array_with_commands[ip] = COS_COMMAND;
            ip += 1;
        }
        else if(strcmp(command, "jmp") == 0)
        {
            CHECK_ERROR(differentJumpsCommands(array_nl_cmd, &array_vb_cmd, JMP_COMMAND,
                                               &characters_were_read, &ip, command, label_name,
                                               NUMBER_OF_LABELS, &fixup, lables_for_assembler));
        }
        else if(strcmp(command, "jb") == 0)
        {
            CHECK_ERROR(differentJumpsCommands(array_nl_cmd, &array_vb_cmd, JB_COMMAND,
                                               &characters_were_read, &ip, command, label_name,
                                               NUMBER_OF_LABELS, &fixup, lables_for_assembler));
        }
        else if(strcmp(command, "call") == 0)
        {
            CHECK_ERROR(differentJumpsCommands(array_nl_cmd, &array_vb_cmd, CALL_COMMAND,
                                               &characters_were_read, &ip, command, label_name,
                                               NUMBER_OF_LABELS, &fixup, lables_for_assembler));
        }
        else if(strcmp(command, "ret") == 0)
        {
            array_nl_cmd->array_with_commands[ip] = RET_COMMAND;
            ip += 1;
        }
        else if(strcmp(command, "prnt") == 0)
        {
            array_nl_cmd->array_with_commands[ip] =PRNT_COMMAND;
            ip += 1;
        }
        else if(strcmp(command, "je") == 0)
        {
            CHECK_ERROR(differentJumpsCommands(array_nl_cmd, &array_vb_cmd, JE_COMMAND,
                                               &characters_were_read, &ip, command, label_name,
                                               NUMBER_OF_LABELS, &fixup, lables_for_assembler));
        }
        else if(strcmp(command, "sqr") == 0)
        {
            array_nl_cmd->array_with_commands[ip] = SQR_COMMAND;
            ip += 1;
        }
        else if(strchr(command, ':') != 0)
        {
            char* colon_address = NULL;
            colon_address = strchr(command, ':');;
            *colon_address = '\0';

            for(int i = 0; i < NUMBER_OF_LABELS; i++)
            {
                if(lables_for_assembler[i].label_address == 0)
                {
                    strcpy(lables_for_assembler[i].label_name, command);

                    lables_for_assembler[i].label_address = ip;
                    break;
                }
                else if(i + 1 == NUMBER_OF_LABELS)
                {
                    return _LABELS_LIM_ERROR;
                }
            }
        }
        else if(strchr(command, ';') != 0)
        {
            while(*(array_vb_cmd.array_with_verbal_commands + characters_were_read) != '\0')
            {
                characters_were_read++;
            }
        }
        else
        {
            fprintf(stdout, "%s\n", command);
            return _SYNTAXIS_ERROR;
        }

        skipSpaces(&array_vb_cmd, &characters_were_read);
    }

    CHECK_ERROR(doFixup(array_nl_cmd, &fixup, lables_for_assembler, NUMBER_OF_LABELS));

    array_nl_cmd->number_of_commands = ip;

    CHECK_ERROR(StackDtor(&fixup));

    return check_error;
}

ErrorNumbers doFixup(info_array_with_commands* array_nl_cmd, stack_info* fixup,
                     labels_info* lables_for_assembler, const int NUMBER_OF_LABELS)
{
    CHECK_NULL_ADDR_ERROR(array_nl_cmd, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(fixup, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(lables_for_assembler, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;
    StackElem_t fixup_element = {};

    while(fixup->size != 0)
    {
        CHECK_ERROR(StackPop(fixup, &fixup_element));

        for(int j = 0; j < NUMBER_OF_LABELS; j++)
        {
            if(strcmp(fixup_element.label_name, lables_for_assembler[j].label_name) == 0)
            {
                array_nl_cmd->array_with_commands[fixup_element.label_address] =
                lables_for_assembler[j].label_address;
            }
        }
    }

    return _NO_ERROR;
}
