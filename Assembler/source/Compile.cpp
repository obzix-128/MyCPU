#include "../include/Compile.h"


ErrorNumbers assemblingCommands(info_array_with_commands* array_nl_cmd,
                               info_array_with_verbal_commands array_vb_cmd)
{
    ErrorNumbers check_error = _NO_ERROR;

    unsigned int ip = 0;
    unsigned int characters_were_read = 0; // TODO: Структуру мб?
    unsigned int command_size = 0;

    const unsigned int _SIZE_OF_THE_COMMAND = 11;
    char command[_SIZE_OF_THE_COMMAND] = {};

    const int NUMBER_OF_LABELS = 10;
    labels_info* lables_for_assembler = (labels_info*) calloc(NUMBER_OF_LABELS, sizeof(labels_info));
    const unsigned int _SIZE_OF_THE_LABEL_NAME = 11;
    char label_name[_SIZE_OF_THE_LABEL_NAME] = {};

    stack_info fixup = {};
    StackElem_t fixup_element = {};

    StackCtor(&fixup);

    while(characters_were_read < array_vb_cmd.size_of_the_array_with_verbal_commands)
    {
        if(ip >= array_nl_cmd->size_of_array_with_commands)
        {
            return _COMMAND_LIM_ERROR;
        }

        sscanf(array_vb_cmd.array_with_verbal_commands + characters_were_read, "%s%n", command,
               (int*)&command_size);
        characters_were_read += command_size + 1;

        if(strcmp(command, "push") == 0)
        {
            array_nl_cmd->array_with_commands[ip] = PUSH_COMMAND;

            sscanf(array_vb_cmd.array_with_verbal_commands + characters_were_read, "%s%n",
                   command, (int*)&command_size);
            characters_were_read += command_size + 1;

            char* pointer = NULL;

            if(strchr(command, 'x'))
            {
                array_nl_cmd->array_with_commands[ip + 1] =
                array_nl_cmd->array_with_commands[ip + 1] | TURN_ON_REGISTERS;

                pointer = strchr(command, 'x');
                array_nl_cmd->array_with_commands[ip + 2] = ((*(pointer - 1) - 'a') + 1);
                if(array_nl_cmd->array_with_commands[ip + 2] > (int)_NUMBER_OF_REGISTERS)
                {
                    return _REGISTER_LIM_ERROR;
                }
            }
            if(strchr(command, '['))
            {
                if(array_nl_cmd->array_with_commands[ip + 1] == 0)
                {
                    array_nl_cmd->array_with_commands[ip + 1] =
                    array_nl_cmd->array_with_commands[ip + 1] | TURN_ON_FIGURE;
                    pointer = strchr(command, '[');
                    sscanf(pointer, "[%d", &array_nl_cmd->array_with_commands[ip + 2]);
                }
                array_nl_cmd->array_with_commands[ip + 1] =
                array_nl_cmd->array_with_commands[ip + 1] | TURN_ON_RAM;
            }
            if(strchr(command, '+'))
            {
                array_nl_cmd->array_with_commands[ip + 1] =
                array_nl_cmd->array_with_commands[ip + 1] | TURN_ON_FIGURE;
                array_nl_cmd->array_with_commands[ip + 1] =
                array_nl_cmd->array_with_commands[ip + 1] | TURN_ON_REGISTERS;

                pointer = strchr(command, '+');
                array_nl_cmd->array_with_commands[ip + 3] =
                array_nl_cmd->array_with_commands[ip + 2];

                sscanf(pointer, "+%d", &array_nl_cmd->array_with_commands[ip + 2]);
                ip += 1;
            }
            if(array_nl_cmd->array_with_commands[ip + 1] == 0)
            {
                array_nl_cmd->array_with_commands[ip + 1] =
                array_nl_cmd->array_with_commands[ip + 1] | TURN_ON_FIGURE;

                sscanf(command, "%d", &array_nl_cmd->array_with_commands[ip + 2]);
            }

            ip += 3;
        }
        else if(strcmp(command, "pop") == 0)
        {
            array_nl_cmd->array_with_commands[ip] = POP_COMMAND;

            sscanf(array_vb_cmd.array_with_verbal_commands + characters_were_read, "%s%n",
                   command, (int*)&command_size);
            characters_were_read += command_size + 1;

            char* pointer = NULL;

            if(strchr(command, 'x'))
            {
                array_nl_cmd->array_with_commands[ip + 1] =
                array_nl_cmd->array_with_commands[ip + 1] | TURN_ON_REGISTERS;

                pointer = strchr(command, 'x');
                array_nl_cmd->array_with_commands[ip + 2] = ((*(pointer - 1) - 'a') + 1);
                if(array_nl_cmd->array_with_commands[ip + 2] > (int)_NUMBER_OF_REGISTERS)
                {
                    return _REGISTER_LIM_ERROR;
                }
            }
            if(strchr(command, '['))
            {
                if(array_nl_cmd->array_with_commands[ip + 1] == 0)
                {
                    array_nl_cmd->array_with_commands[ip + 1] =
                    array_nl_cmd->array_with_commands[ip + 1] | TURN_ON_FIGURE;
                    pointer = strchr(command, '[');
                    sscanf(pointer, "[%d", &array_nl_cmd->array_with_commands[ip + 2]);
                }
                array_nl_cmd->array_with_commands[ip + 1] =
                array_nl_cmd->array_with_commands[ip + 1] | TURN_ON_RAM;
            }
            if(strchr(command, '+'))
            {
                array_nl_cmd->array_with_commands[ip + 1] =
                array_nl_cmd->array_with_commands[ip + 1] | TURN_ON_FIGURE;
                array_nl_cmd->array_with_commands[ip + 1] =
                array_nl_cmd->array_with_commands[ip + 1] | TURN_ON_REGISTERS;

                pointer = strchr(command, '+');
                array_nl_cmd->array_with_commands[ip + 3] =
                array_nl_cmd->array_with_commands[ip + 2];

                sscanf(pointer, "+%d", &array_nl_cmd->array_with_commands[ip + 2]);
                ip += 1;
            }

            ip += 3;
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
            sscanf(array_vb_cmd.array_with_verbal_commands + characters_were_read, "%s%n", label_name,
                   (int*)&command_size);
            characters_were_read += command_size + 1;

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
                    array_nl_cmd->array_with_commands[ip] = JMP_COMMAND;
                    array_nl_cmd->array_with_commands[ip + 1] = lables_for_assembler[i].label_address;
                    break;
                }
            }

            if(array_nl_cmd->array_with_commands[ip] == 0)
            {
                strcpy(fixup_element.label_name, label_name);
                fixup_element.label_address = ip + 1;

                StackPush(&fixup, fixup_element);

                array_nl_cmd->array_with_commands[ip] = JMP_COMMAND;
                array_nl_cmd->array_with_commands[ip + 1] = -1;
            }
            ip += 2;
        }
        else if(strcmp(command, "jb") == 0)
        {
            sscanf(array_vb_cmd.array_with_verbal_commands + characters_were_read, "%s%n", label_name,
                   (int*)&command_size);
            characters_were_read += command_size + 1;
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
                    array_nl_cmd->array_with_commands[ip] = JB_COMMAND;
                    array_nl_cmd->array_with_commands[ip + 1] = lables_for_assembler[i].label_address;
                    break;
                }
            }

            if(array_nl_cmd->array_with_commands[ip] == 0)
            {
                strcpy(fixup_element.label_name, label_name);
                fixup_element.label_address = ip + 1;

                StackPush(&fixup, fixup_element);

                array_nl_cmd->array_with_commands[ip] = JB_COMMAND;
                array_nl_cmd->array_with_commands[ip + 1] = -1;
            }
            ip += 2;
        }
        else if(strcmp(command, "call") == 0)
        {
            sscanf(array_vb_cmd.array_with_verbal_commands + characters_were_read, "%s%n", label_name,
                   (int*)&command_size);
            characters_were_read += command_size + 1;
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
                    array_nl_cmd->array_with_commands[ip] = CALL_COMMAND;
                    array_nl_cmd->array_with_commands[ip + 1] = lables_for_assembler[i].label_address;
                    break;
                }
            }

            if(array_nl_cmd->array_with_commands[ip] == 0)
            {
                strcpy(fixup_element.label_name, label_name);
                fixup_element.label_address = ip + 1;

                StackPush(&fixup, fixup_element);

                array_nl_cmd->array_with_commands[ip] = CALL_COMMAND;
                array_nl_cmd->array_with_commands[ip + 1] = -1;
            }
            ip += 2;
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
        else if(strchr(command, ':') != 0)
        {
            char* colon_address = NULL;
            colon_address = strchr(command, ':');
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
        else
        {
            fprintf(stdout, "%s\n", command);
            return _SYNTAXIS_ERROR;
        }
    }

    while(fixup.size != 0)
    {
        StackPop(&fixup, &fixup_element);

        for(int j = 0; j < NUMBER_OF_LABELS; j++)
        {
            if(strcmp(fixup_element.label_name, lables_for_assembler[j].label_name) == 0)
            {
                array_nl_cmd->array_with_commands[fixup_element.label_address] =
                lables_for_assembler[j].label_address;
            }
        }
    }

    array_nl_cmd->number_of_commands = ip;

    StackDtor(&fixup);

    return check_error;
}
