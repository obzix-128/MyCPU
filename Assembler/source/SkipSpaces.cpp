#include "../include/SkipSpaces.h"


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
