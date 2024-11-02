#include "../include/ExecuteCommands.h"
#include "../include/Commands.h"


ErrorNumbers executeCurrentCommand(info_array_with_commands_code* executable_code,
                                   StackElem_t registers[], StackElem_t random_access_memory[],
                                   stack_info* my_stack, stack_info* return_address)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(registers, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(random_access_memory, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(my_stack, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    switch(executable_code->code[executable_code->ip] & ONLY_COMMAND)
    {
        case PUSH_COMMAND:
        {
            CHECK_ERROR(pushCommand(executable_code, registers, random_access_memory, my_stack));
            break;
        }
        case POP_COMMAND:
        {
            CHECK_ERROR(popCommand(executable_code, registers, random_access_memory, my_stack));
            break;
        }
        case OUT_COMMAND:
        {
            CHECK_ERROR(outCommand(executable_code, my_stack));
            break;
        }
        case DUMP_COMMAND:
        {
            CHECK_ERROR(dumpCommand(executable_code, my_stack));
            break;
        }
        case HLT_COMMAND:
        {
            CHECK_ERROR(hltCommand(executable_code));
            break;
        }
        case IN_COMMAND:
        {
            CHECK_ERROR(inCommand(executable_code, my_stack));
            break;
        }
        case ADD_COMMAND:
        {
            CHECK_ERROR(addCommand(executable_code, my_stack));
            break;
        }
        case SUB_COMMAND:
        {
            CHECK_ERROR(subCommand(executable_code, my_stack));
            break;
        }
        case MUL_COMMAND:
        {
            CHECK_ERROR(mulCommand(executable_code, my_stack));
            break;
        }
        case DIV_COMMAND:
        {
            CHECK_ERROR(divCommand(executable_code, my_stack));
            break;
        }
        case SQRT_COMMAND:
        {
            CHECK_ERROR(sqrtCommand(executable_code, my_stack));
            break;
        }
        case SIN_COMMAND:
        {
            CHECK_ERROR(sinCommand(executable_code, my_stack));
            break;
        }
        case COS_COMMAND:
        {
            CHECK_ERROR(cosCommand(executable_code, my_stack));
            break;
        }
        case JMP_COMMAND:
        {
            CHECK_ERROR(jmpCommand(executable_code));
            break;
        }
        case JB_COMMAND:
        {
            CHECK_ERROR(jbCommand(executable_code, my_stack));
            break;
        }
        case CALL_COMMAND:
        {
            CHECK_ERROR(callCommand(executable_code, return_address));
            break;
        }
        case RET_COMMAND:
        {
            CHECK_ERROR(retCommand(executable_code, return_address));
            break;
        }
        case PRNT_COMMAND:
        {
            CHECK_ERROR(prntCommand(executable_code, random_access_memory));
            break;
        }
        default:
        {
            return _SYNTAXIS_ERROR;
            break;
        }
    }

    return check_error;
}

ErrorNumbers executeCommands(info_array_with_commands_code* executable_code)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    struct stack_info my_stack = {};
    CHECK_ERROR(StackCtor(&my_stack));

    struct stack_info return_address = {};
    CHECK_ERROR(StackCtor(&return_address));

    StackElem_t registers[_NUMBER_OF_REGISTERS] = {};
    StackElem_t random_access_memory[_SIZE_OF_RAM] = {};

    while(executable_code->ip < executable_code->size_of_code)
    {
        CHECK_ERROR(executeCurrentCommand(executable_code, registers, random_access_memory,
                                          &my_stack, &return_address));
    }

    CHECK_ERROR(StackDtor(&my_stack));
    CHECK_ERROR(StackDtor(&return_address));

    return _NO_ERROR;
}

StackElem_t* getArguments(info_array_with_commands_code* executable_code, StackElem_t registers[],
                          StackElem_t random_access_memory[])
{
    assert(executable_code);
    assert(registers);
    assert(random_access_memory);

    int argument_type = executable_code->code[executable_code->ip] & ONLY_MARKERS;
    executable_code->ip++;
    StackElem_t* argument_value = NULL;

    if(argument_type & TURN_ON_IMMED)
    {
        argument_value = &executable_code->code[executable_code->ip];
        executable_code->ip++;
    }

    if(argument_type & TURN_ON_REGISTERS)
    {
        if(argument_type & TURN_ON_IMMED)
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
