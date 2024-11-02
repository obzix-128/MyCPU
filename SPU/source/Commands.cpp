#include "../include/Commands.h"
#include "../include/ExecuteCommands.h"


ErrorNumbers pushCommand(info_array_with_commands_code* executable_code, StackElem_t registers[],
                         StackElem_t random_access_memory[], stack_info* my_stack)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(registers, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(random_access_memory, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(my_stack, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;
    StackElem_t first = 0;
    first = (int) getArguments(executable_code, registers, random_access_memory);
    CHECK_ERROR(StackPush(my_stack, *((int*) first)));
    return _NO_ERROR;
}

ErrorNumbers popCommand(info_array_with_commands_code* executable_code, StackElem_t registers[],
                        StackElem_t random_access_memory[], stack_info* my_stack)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(registers, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(random_access_memory, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(my_stack, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;
    CHECK_ERROR(StackPop(my_stack, getArguments(executable_code, registers,
                                                random_access_memory)));
    return _NO_ERROR;
}

ErrorNumbers outCommand(info_array_with_commands_code* executable_code, stack_info* my_stack)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(my_stack, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;
    StackElem_t first = 0;

    CHECK_ERROR(StackPop(my_stack, &first));
    printf(STACK_ELEM_T "\n", first);
    executable_code->ip++;
    return _NO_ERROR;
}

ErrorNumbers dumpCommand(info_array_with_commands_code* executable_code, stack_info* my_stack)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(my_stack, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    CHECK_ERROR(StackDump(my_stack));
    executable_code->ip++;
    return _NO_ERROR;
}

ErrorNumbers hltCommand(info_array_with_commands_code* executable_code)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);

    executable_code->ip = executable_code->size_of_code;
    return _NO_ERROR;
}

ErrorNumbers inCommand(info_array_with_commands_code* executable_code, stack_info* my_stack)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(my_stack, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;
    StackElem_t first = 0;

    fprintf(stdout, "Please enter a number\n");
    scanf(STACK_ELEM_T, &first);
    CHECK_ERROR(StackPush(my_stack, first));
    executable_code->ip++;
    return _NO_ERROR;
}

ErrorNumbers addCommand(info_array_with_commands_code* executable_code, stack_info* my_stack)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(my_stack, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;
    StackElem_t first = 0;
    StackElem_t second = 0;

    CHECK_ERROR(StackPop(my_stack, &first));
    CHECK_ERROR(StackPop(my_stack, &second));
    CHECK_ERROR(StackPush(my_stack, first + second));
    executable_code->ip++;
    return _NO_ERROR;
}

ErrorNumbers subCommand(info_array_with_commands_code* executable_code, stack_info* my_stack)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(my_stack, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;
    StackElem_t first = 0;
    StackElem_t second = 0;

    CHECK_ERROR(StackPop(my_stack, &first));
    CHECK_ERROR(StackPop(my_stack, &second));
    CHECK_ERROR(StackPush(my_stack, second - first));
    executable_code->ip++;
    return _NO_ERROR;
}

ErrorNumbers mulCommand(info_array_with_commands_code* executable_code, stack_info* my_stack)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(my_stack, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;
    StackElem_t first = 0;
    StackElem_t second = 0;

    CHECK_ERROR(StackPop(my_stack, &first));
    CHECK_ERROR(StackPop(my_stack, &second));
    CHECK_ERROR(StackPush(my_stack, second * first));
    executable_code->ip++;

    return _NO_ERROR;
}

ErrorNumbers divCommand(info_array_with_commands_code* executable_code, stack_info* my_stack)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(my_stack, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;
    StackElem_t first = 0;
    StackElem_t second = 0;

    CHECK_ERROR(StackPop(my_stack, &first));
    CHECK_ERROR(StackPop(my_stack, &second));
    CHECK_ERROR(StackPush(my_stack, second / first));
    executable_code->ip++;

    return _NO_ERROR;
}

ErrorNumbers sqrtCommand(info_array_with_commands_code* executable_code, stack_info* my_stack)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(my_stack, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;
    StackElem_t first = 0;

    CHECK_ERROR(StackPop(my_stack, &first));
    CHECK_ERROR(StackPush(my_stack, (int)sqrt(first)));
    executable_code->ip++;

    return _NO_ERROR;
}

ErrorNumbers sinCommand(info_array_with_commands_code* executable_code, stack_info* my_stack)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(my_stack, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;
    StackElem_t first = 0;

    CHECK_ERROR(StackPop(my_stack, &first));
    CHECK_ERROR(StackPush(my_stack, (int)sin(first)));
    executable_code->ip++;

    return _NO_ERROR;
}

ErrorNumbers cosCommand(info_array_with_commands_code* executable_code, stack_info* my_stack)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(my_stack, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;
    StackElem_t first = 0;

    CHECK_ERROR(StackPop(my_stack, &first));
    CHECK_ERROR(StackPush(my_stack, (int)cos(first)));
    executable_code->ip++;

    return _NO_ERROR;
}

ErrorNumbers jmpCommand(info_array_with_commands_code* executable_code)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);

    executable_code->ip++;
    executable_code->ip = executable_code->code[executable_code->ip];

    return _NO_ERROR;
}

ErrorNumbers jbCommand(info_array_with_commands_code* executable_code, stack_info* my_stack)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(my_stack, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;
    StackElem_t first = 0;
    StackElem_t second = 0;

    CHECK_ERROR(StackPop(my_stack, &first));
    CHECK_ERROR(StackPop(my_stack, &second));

    if(second <= first)
    {
        executable_code->ip++;
        executable_code->ip = executable_code->code[executable_code->ip];
    }
    else
    {
        executable_code->ip += 2;
    }

    return _NO_ERROR;
}

ErrorNumbers callCommand(info_array_with_commands_code* executable_code, stack_info* return_address)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(return_address, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    CHECK_ERROR(StackPush(return_address, executable_code->ip + 2));
    executable_code->ip++;
    executable_code->ip = executable_code->code[executable_code->ip];

    return _NO_ERROR;
}

ErrorNumbers retCommand(info_array_with_commands_code* executable_code, stack_info* return_address)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(return_address, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    CHECK_ERROR(StackPop(return_address, (int*)&executable_code->ip));

    return _NO_ERROR;
}

ErrorNumbers prntCommand(info_array_with_commands_code* executable_code,
                         StackElem_t random_access_memory[])
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(random_access_memory, _NULL_ADDRESS_ERROR);

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

    return _NO_ERROR;
}
