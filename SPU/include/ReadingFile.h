#ifndef READINGFILE_H
#define READINGFILE_H

#include "Processor.h"
#include <sys/stat.h>

ErrorNumbers readFileWithCommands(info_array_with_commands_txt* commands, const char* file_name);


#endif //READINGFILE_H
