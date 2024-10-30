#include "../include/Assembler.h"
#include "../include/TextHandler.h"
#include "../include/errorHandler.h"
#include "../include/Compile.h"


int main(const int argc, const char** argv)
{
    const int _NUMBERS_OF_ARGUMENTS = 3;
    if(argc != _NUMBERS_OF_ARGUMENTS)
    {
        errorHandler(_FILE_NAME_ERROR);
        return _FILE_NAME_ERROR;
    }

    ErrorNumbers check_error = _NO_ERROR;

    info_array_with_verbal_commands array_vb_cmd = {};
    info_array_with_commands array_nl_cmd = {};

    check_error = readFile(&array_vb_cmd, argv[1]);
    if(check_error != _NO_ERROR)
    {
        errorHandler(check_error);
        return check_error;
    }

    array_nl_cmd.size_of_array_with_commands = _SIZE_OF_THE_ARRAY_WITH_COMMANDS;

    array_nl_cmd.array_with_commands = (int*) calloc(_SIZE_OF_THE_ARRAY_WITH_COMMANDS, sizeof(int));

    check_error = assemblingCommands(&array_nl_cmd, array_vb_cmd);
    if(check_error != _NO_ERROR)
    {
        errorHandler(check_error);
        return check_error;
    }

    check_error = writeCommands(array_nl_cmd, argv[2]);
    if(check_error != _NO_ERROR)
    {
        errorHandler(check_error);
        return check_error;
    }

    printf("DONE\n");

    return _NO_ERROR;
}
