#include "../include/Processor.h"


int main(const int argc, const char** argv)
{
    const int _NUMBERS_OF_ARGUMENTS = 2;
    if(argc != _NUMBERS_OF_ARGUMENTS)
    {
        errorHandler(_FILE_NAME_ERROR);
        return _FILE_NAME_ERROR;
    }

    ErrorNumbers check_error = _NO_ERROR;

    struct info_array_with_commands_txt commands = {};

    check_error = readFileWithCommands(&commands, argv[1]);
    if(check_error != _NO_ERROR)
    {
        errorHandler(check_error);
        return check_error;
    }

    check_error = checkVersion(&commands);
    if(check_error != _NO_ERROR)
    {
        errorHandler(check_error);
        return check_error;
    }

    struct info_array_with_commands_code executable_code = {};

    check_error = processingAnArrayOfCommands(&commands, &executable_code);
    if(check_error != _NO_ERROR)
    {
        errorHandler(check_error);
        return check_error;
    }

    check_error = executeCommands(&executable_code);
    if(check_error != _NO_ERROR)
    {
        errorHandler(check_error);
        return check_error;
    }

    printf("DONE\n");

    return NO_ERROR;
}

