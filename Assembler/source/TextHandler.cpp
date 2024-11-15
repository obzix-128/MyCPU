#include "../include/TextHandler.h"


ErrorNumbers combiningStrings(const char* first, const char* second, char** result)
{
    CHECK_NULL_ADDR_ERROR(first, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(second, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(result, _NULL_ADDRESS_ERROR);

    int size_file_name = strlen(first);
    size_file_name += strlen(second);

    *result = (char*) calloc(size_file_name, sizeof(char));
    CHECK_NULL_ADDR_ERROR(*result, _CALLOC_ERROR);

    sprintf(*result, "%s%s", first, second);

    return _NO_ERROR;
}

ErrorNumbers readFile(info_array_with_verbal_commands* array_vb_cmd, const char* full_file_name)
{
    CHECK_NULL_ADDR_ERROR(array_vb_cmd, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(full_file_name, _FILE_NAME_ERROR);

    ErrorNumbers check_error = _NO_ERROR;
    struct stat file_info = {};

    CHECK_ERROR((ErrorNumbers)stat(full_file_name, &file_info))

    array_vb_cmd->size_of_the_array_with_verbal_commands = file_info.st_size;

    FILE* file_with_verbal_commands  = fopen(full_file_name,  "r");
    CHECK_NULL_ADDR_ERROR(file_with_verbal_commands, _OPEN_ERROR);

    array_vb_cmd->array_with_verbal_commands =
    (char*) calloc(array_vb_cmd->size_of_the_array_with_verbal_commands, sizeof(char));
    CHECK_NULL_ADDR_ERROR(array_vb_cmd->array_with_verbal_commands, _CALLOC_ERROR);

    array_vb_cmd->size_of_the_array_with_verbal_commands =
    fread(array_vb_cmd->array_with_verbal_commands, sizeof(char),
          array_vb_cmd->size_of_the_array_with_verbal_commands, file_with_verbal_commands);

    CHECK_ERROR(textProcessing(array_vb_cmd));

    fclose(file_with_verbal_commands);
    return check_error;
}

ErrorNumbers textProcessing(info_array_with_verbal_commands* array_vb_cmd)
{
    CHECK_NULL_ADDR_ERROR(array_vb_cmd, _NULL_ADDRESS_ERROR)

    for(unsigned int i = 0; i < array_vb_cmd->size_of_the_array_with_verbal_commands; i++)
    {
        if(array_vb_cmd->array_with_verbal_commands[i] == '\n')
        {
            array_vb_cmd->array_with_verbal_commands[i] = '\0';
        }
    }

    for(unsigned int i = 0; i < array_vb_cmd->size_of_the_array_with_verbal_commands; i++)
    {
        if(array_vb_cmd->array_with_verbal_commands[i] == ';')
        {
            while(array_vb_cmd->array_with_verbal_commands[i] != '\0')
            {
                array_vb_cmd->array_with_verbal_commands[i] = '\0';
                i++;
            }
        }
    }

    return _NO_ERROR;
}

ErrorNumbers writeCommands(info_array_with_commands array_nl_cmd, const char* full_file_name)
{
    CHECK_NULL_ADDR_ERROR(full_file_name, _FILE_NAME_ERROR);

    FILE* file_with_numeral_commands = fopen(full_file_name, "wb");
    CHECK_NULL_ADDR_ERROR(file_with_numeral_commands, _OPEN_ERROR);

    fwrite(&_SIGNATURE_, sizeof(int), 1, file_with_numeral_commands);
    fwrite(&_ASSEMBLER_VERSION_, sizeof(int), 1, file_with_numeral_commands);

    const int _SIZE_ALIGNMENT = 2;
    const int ALIGNMENT[_SIZE_ALIGNMENT] = {};
    fwrite(ALIGNMENT, sizeof(int), _SIZE_ALIGNMENT, file_with_numeral_commands);

    fwrite(array_nl_cmd.array_with_commands, sizeof(int), array_nl_cmd.number_of_commands,
           file_with_numeral_commands);

    fclose(file_with_numeral_commands);

    return _NO_ERROR;
}

ErrorNumbers skipSpaces(info_array_with_verbal_commands* array_vb_cmd,
                        unsigned int* characters_were_read)
{
    CHECK_NULL_ADDR_ERROR(array_vb_cmd, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(characters_were_read, _NULL_ADDRESS_ERROR);

    while(true)
    {
        if(*(array_vb_cmd->array_with_verbal_commands + *characters_were_read) != '\0' &&
           *(array_vb_cmd->array_with_verbal_commands + *characters_were_read) != ' ')
        {
            break;
        }
        else
        {
            (*characters_were_read)++;
        }
    }

    return _NO_ERROR;
}
