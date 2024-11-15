#include "../include/Assembler.h"
#include "../include/TextHandler.h"
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

    const char* WAY_TO_FILE_FOR_READ  = "CommandsFilesVer/";
    char* full_file_name = NULL;

    CHECK_ERROR(combiningStrings(WAY_TO_FILE_FOR_READ, argv[1], &full_file_name));
    CHECK_ERROR(readFile(&array_vb_cmd, full_file_name));

    array_nl_cmd.size_of_array_with_commands = _SIZE_OF_THE_ARRAY_WITH_COMMANDS;

    array_nl_cmd.array_with_commands = (int*) calloc(_SIZE_OF_THE_ARRAY_WITH_COMMANDS, sizeof(int));
    CHECK_NULL_ADDR_ERROR(array_nl_cmd.array_with_commands, _CALLOC_ERROR);

    CHECK_ERROR(assemblingCommands(&array_nl_cmd, &array_vb_cmd));

    const char* WAY_TO_FILE_FOR_WRITE  = "CommandsFilesNum/";

    CHECK_ERROR(combiningStrings(WAY_TO_FILE_FOR_WRITE, argv[2], &full_file_name));
    CHECK_ERROR(writeCommands(array_nl_cmd, full_file_name));

    printf("DONE\n");

    return _NO_ERROR;
}
