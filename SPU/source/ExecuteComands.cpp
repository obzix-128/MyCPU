#include "../include/ExecuteCommands.h"


ErrorNumbers executeCommands(info_array_with_commands_code* executable_code)
{
    struct stack_info my_stack = {};
    StackCtor(&my_stack);
    struct stack_info return_address = {};
    StackCtor(&return_address);
    StackElem_t registers[_NUMBER_OF_REGISTERS] = {};
    StackElem_t random_access_memory[_SIZE_OF_RAM] = {};
    StackElem_t first = 0;
    StackElem_t second = 0;

    while(executable_code->ip < executable_code->size_of_code)
    {
        switch(executable_code->code[executable_code->ip])
        {
            case PUSH_COMMAND:
            {
                first = (int) getArguments(executable_code, registers, random_access_memory);
                StackPush(&my_stack, *((int*) first));
                break;
            }
            case POP_COMMAND:
            {
                StackPop(&my_stack, getArguments(executable_code, registers, random_access_memory));
                break;
            }
            case OUT_COMMAND:
            {
                StackPop(&my_stack, &first);
                printf(STACK_ELEM_T "\n", first);
                executable_code->ip++;
                break;
            }
            case DUMP_COMMAND:
            {
                StackDump(&my_stack);
                executable_code->ip++;
                break;
            }
            case HLT_COMMAND:
            {
                return _NO_ERROR;
                executable_code->ip++;
                break;
            }
            case IN_COMMAND:
            {
                fprintf(stdout, "Please enter a number\n");
                scanf(STACK_ELEM_T, &first);
                StackPush(&my_stack, first);
                executable_code->ip++;
                break;
            }
            case ADD_COMMAND:
            {
                StackPop(&my_stack, &first);
                StackPop(&my_stack, &second);
                StackPush(&my_stack, first + second);
                executable_code->ip++;
                break;
            }
            case SUB_COMMAND:
            {
                StackPop(&my_stack, &first);
                StackPop(&my_stack, &second);
                StackPush(&my_stack, second - first);
                executable_code->ip++;
                break;
            }
            case MUL_COMMAND:
            {
                StackPop(&my_stack, &first);
                StackPop(&my_stack, &second);
                StackPush(&my_stack, second * first);
                executable_code->ip++;
                break;
            }
            case DIV_COMMAND:
            {
                StackPop(&my_stack, &first);
                StackPop(&my_stack, &second);
                StackPush(&my_stack, second / first);
                executable_code->ip++;
                break;
            }
            case SQRT_COMMAND:
            {
                StackPop(&my_stack, &first);
                StackPush(&my_stack, (int)sqrt(first));
                executable_code->ip++;
                break;
            }
            case SIN_COMMAND:
            {
                StackPop(&my_stack, &first);
                StackPush(&my_stack, (int)sin(first));
                executable_code->ip++;
                break;
            }
            case COS_COMMAND:
            {
                StackPop(&my_stack, &first);
                StackPush(&my_stack, (int)cos(first));
                executable_code->ip++;
                break;
            }
            case JMP_COMMAND:
            {
                executable_code->ip++;
                executable_code->ip = executable_code->code[executable_code->ip];
                break;
            }
            case JB_COMMAND:
            {
                StackPop(&my_stack, &first);
                StackPop(&my_stack, &second);

                if(second <= first)
                {
                    executable_code->ip++;
                    executable_code->ip = executable_code->code[executable_code->ip];
                }
                else
                {
                    executable_code->ip += 2;
                }
                break;
            }
            case CALL_COMMAND:
            {
                StackPush(&return_address, executable_code->ip + 2);
                executable_code->ip++;
                executable_code->ip = executable_code->code[executable_code->ip];
                break;
            }
            case RET_COMMAND:
            {
                StackPop(&return_address, (int*)&executable_code->ip);
                break;
            }
            case PRNT_COMMAND:
            {
                const int _NUMBER_OF_LINES = 10;
                for(int i = 0; i < _NUMBER_OF_LINES; i++)
                {
                    for(int j = 0; j < _SIZE_OF_RAM / _NUMBER_OF_LINES; j++)
                    {
                        if(random_access_memory[i * _NUMBER_OF_LINES + j] == 0)
                        {
                            fprintf(stdout, ".");
                        }
                        else
                        {
                            fprintf(stdout, "*");
                        }
                    }
                    fprintf(stdout, "\n");
                }
                executable_code->ip++;
                break;
            }
            default:
            {
                return _SYNTAXIS_ERROR;
                break;
            }
        }
    }
    StackDtor(&my_stack);
    StackDtor(&return_address);

    return _NO_ERROR;
}

StackElem_t* getArguments(info_array_with_commands_code* executable_code, StackElem_t registers[],
                    StackElem_t random_access_memory[])
{
    int operation = executable_code->code[executable_code->ip];
    operation++; // TODO: Отрубить warning
    executable_code->ip++;
    int argument_type = executable_code->code[executable_code->ip];
    executable_code->ip++;
    StackElem_t* argument_value = NULL;
    if(argument_type & TURN_ON_FIGURE)
    {
        argument_value = &executable_code->code[executable_code->ip];
        executable_code->ip++;
    }
    if(argument_type & TURN_ON_REGISTERS)
    {
        if(argument_type & TURN_ON_FIGURE)
        {
            registers[0] = *argument_value + registers[executable_code->code[executable_code->ip]];
            argument_value = &registers[0];
            executable_code->ip++;
        }
        else
        {
            argument_value = &registers[executable_code->code[executable_code->ip]];
            executable_code->ip++;
        }
    }
    if(argument_type & TURN_ON_RAM)
    {
        if(*argument_value > _SIZE_OF_RAM)
        {
            assert(0);
        }
        argument_value = &random_access_memory[*argument_value];
    }
    return argument_value;
}
