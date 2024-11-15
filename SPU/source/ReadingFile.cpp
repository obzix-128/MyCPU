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

ErrorNumbers readFileWithCommands(info_array_with_commands_code* executable_code,
                                  const char* full_file_name)
{
    CHECK_NULL_ADDR_ERROR(full_file_name, _FILE_NAME_ERROR);
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);

    struct stat file_info = {};
    ErrorNumbers check_error = _NO_ERROR;

    CHECK_ERROR((ErrorNumbers)stat(full_file_name, &file_info));

    executable_code->size_of_code = file_info.st_size / sizeof(int);

    FILE* file_with_numeral_commands = fopen(full_file_name, "rb");
    CHECK_NULL_ADDR_ERROR(file_with_numeral_commands, _OPEN_ERROR);

    executable_code->code = (int*) calloc(executable_code->size_of_code, sizeof(int));
    CHECK_NULL_ADDR_ERROR(executable_code->code, _CALLOC_ERROR);

    executable_code->size_of_code = fread(executable_code->code, sizeof(int),
                                          executable_code->size_of_code, file_with_numeral_commands);

    fclose(file_with_numeral_commands);

    return check_error;
}

ErrorNumbers checkVersion(info_array_with_commands_code* executable_code)
{
    CHECK_NULL_ADDR_ERROR(executable_code, _NULL_ADDRESS_ERROR);

    if(executable_code->code[0] != _SIGNATURE_)
    {
        return _SIGNATURE_ERROR;
    }
    executable_code->code += 1;
    executable_code->size_of_code -= 1;

    if(executable_code->code[0] != _ASSEMBLER_VERSION_)
    {
        return _SIGNATURE_ERROR;
    }
    executable_code->code += 1;
    executable_code->size_of_code -= 1;

    const int ALIGNMENT = 2;
    executable_code->code = executable_code->code + ALIGNMENT;
    executable_code->size_of_code = executable_code->size_of_code - ALIGNMENT;

    return _NO_ERROR;
}
