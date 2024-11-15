#include "../include/Processor.h"
#include "../include/ErrorHandler.h"
#include "../include/ReadingFile.h"
#include "../include/ExecuteCommands.h"


int main(const int argc, const char** argv)
{
    const int _NUMBERS_OF_ARGUMENTS = 2;
    if(argc != _NUMBERS_OF_ARGUMENTS)
    {
        errorHandler(_FILE_NAME_ERROR);
        return _FILE_NAME_ERROR;
    }

    ErrorNumbers check_error = _NO_ERROR;

    struct info_array_with_commands_code executable_code = {};

    const char* WAY_TO_FILE  = "CommandsFilesNum/";
    char* full_file_name = NULL;

    CHECK_ERROR(combiningStrings(WAY_TO_FILE, argv[1], &full_file_name));
    CHECK_ERROR(readFileWithCommands(&executable_code, full_file_name));
    CHECK_ERROR(checkVersion(&executable_code));

    CHECK_ERROR(executeCommands(&executable_code));

    printf("DONE\n");

    return _NO_ERROR;
}

