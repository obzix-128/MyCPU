#include "../include/ReadingFile.h"


ErrorNumbers readFileWithCommands(info_array_with_commands_txt* commands, const char* file_name)
{
    if(file_name == NULL)
    {
        return _FILE_NAME_ERROR;
    }

    struct stat file_info = {};

    const char* WAY_TO_FILE  = "../CommandsFilesNum/";
    int size_file_name = strlen(WAY_TO_FILE);
    size_file_name += strlen(file_name);

    char* full_file_name = (char*) calloc(size_file_name, sizeof(char));

    sprintf(full_file_name, "%s%s", WAY_TO_FILE, file_name);

    if(stat(full_file_name, &file_info) == -1)
    {
        return _STAT_ERROR;
    }

    commands->size_of_array = file_info.st_size;

    FILE* file_with_numeral_commands = fopen(full_file_name, "r");
    if(file_with_numeral_commands == NULL)
    {
        return _OPEN_ERROR;
    }

    commands->array = (char*) calloc(commands->size_of_array, sizeof(char));
    if(commands->array == NULL)
    {
        fclose(file_with_numeral_commands);
        return _CALLOC_ERROR;
    }

    commands->size_of_array = fread(commands->array, sizeof(char), commands->size_of_array,
                                   file_with_numeral_commands);

    fclose(file_with_numeral_commands);

    return _NO_ERROR;
}
