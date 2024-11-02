#include "../include/ReadingFile.h"


ErrorNumbers combiningStrings(const char* first, const char* second, char** result)
{
    int size_file_name = strlen(first);
    size_file_name += strlen(second);

    *result = (char*) calloc(size_file_name, sizeof(char));
    CHECK_NULL_ADDR_ERROR(*result, _CALLOC_ERROR);

    sprintf(*result, "%s%s", first, second);

    return _NO_ERROR;
}

ErrorNumbers readFileWithCommands(info_array_with_commands_txt* commands, const char* full_file_name)
{
    CHECK_NULL_ADDR_ERROR(full_file_name, _FILE_NAME_ERROR);
    CHECK_NULL_ADDR_ERROR(commands, _NULL_ADDRESS_ERROR);

    struct stat file_info = {};
    ErrorNumbers check_error = _NO_ERROR;

    CHECK_ERROR((ErrorNumbers)stat(full_file_name, &file_info));

    commands->size_of_array = file_info.st_size;

    FILE* file_with_numeral_commands = fopen(full_file_name, "r");
    CHECK_NULL_ADDR_ERROR(file_with_numeral_commands, _OPEN_ERROR);

    commands->array = (char*) calloc(commands->size_of_array, sizeof(char));
    CHECK_NULL_ADDR_ERROR(commands->array, _CALLOC_ERROR);

    commands->size_of_array = fread(commands->array, sizeof(char), commands->size_of_array,
                                   file_with_numeral_commands);

    fclose(file_with_numeral_commands);

    return check_error;
}
