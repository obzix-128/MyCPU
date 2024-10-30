#include "../include/TextHandler.h"


ErrorNumbers readFile(info_array_with_verbal_commands* array_vb_cmd, const char* file_name)
{
    if(file_name == NULL)
    {
        return _FILE_NAME_ERROR;
    }

    struct stat file_info = {};

    const char* WAY_TO_FILE  = "../CommandsFilesVer/";
    int size_file_name = strlen(WAY_TO_FILE);
    size_file_name += strlen(file_name);

    char* full_file_name = (char*) calloc(size_file_name, sizeof(char));

    sprintf(full_file_name, "%s%s", WAY_TO_FILE, file_name);

    if(stat(full_file_name, &file_info) == -1)
    {
        return _STAT_ERROR;
    }

    array_vb_cmd->size_of_the_array_with_verbal_commands = file_info.st_size;

    FILE* file_with_verbal_commands  = fopen(full_file_name,  "r");
    if(file_with_verbal_commands == NULL)
    {
        return _OPEN_ERROR;
    }

    array_vb_cmd->array_with_verbal_commands =
    (char*) calloc(array_vb_cmd->size_of_the_array_with_verbal_commands, sizeof(char));
    if(array_vb_cmd->array_with_verbal_commands == NULL)
    {
        fclose(file_with_verbal_commands);
        return _CALLOC_ERROR;
    }

    array_vb_cmd->size_of_the_array_with_verbal_commands =
    fread(array_vb_cmd->array_with_verbal_commands, sizeof(char),
          array_vb_cmd->size_of_the_array_with_verbal_commands, file_with_verbal_commands);

    textProcessing(array_vb_cmd);

    fclose(file_with_verbal_commands);
    return _NO_ERROR;
}

ErrorNumbers textProcessing(info_array_with_verbal_commands* array_vb_cmd)
{
    for(unsigned int i = 0; i < array_vb_cmd->size_of_the_array_with_verbal_commands; i++)
    {
        if(array_vb_cmd->array_with_verbal_commands[i] == '\n')
        {
            array_vb_cmd->array_with_verbal_commands[i] = '\0';
        }
    }

    return _NO_ERROR;
}

ErrorNumbers writeCommands(info_array_with_commands array_nl_cmd, const char* file_name)
{
    if(file_name == NULL)
    {
        return _FILE_NAME_ERROR;
    }

    const char* WAY_TO_FILE  = "../CommandsFilesNum/";
    int size_file_name = strlen(WAY_TO_FILE);
    size_file_name += strlen(file_name);

    char* full_file_name = (char*) calloc(size_file_name, sizeof(char));

    sprintf(full_file_name, "%s%s", WAY_TO_FILE, file_name);

    FILE* file_with_numeral_commands = fopen(full_file_name, "w");
    if(file_with_numeral_commands == NULL)
    {
        fclose(file_with_numeral_commands);
        return _OPEN_ERROR;
    }

    fprintf(file_with_numeral_commands, _SIGNATURE_ "\n" _ASSEMBLER_VERSION_ "\n");

    for(unsigned int i = 0; i < array_nl_cmd.number_of_commands; i++)
    {
        fprintf(file_with_numeral_commands, "%x ", array_nl_cmd.array_with_commands[i]);
    }
    fclose(file_with_numeral_commands);

    return _NO_ERROR;
}
