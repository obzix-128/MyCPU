#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H

#include "Assembler.h"

#include <sys/stat.h>
ErrorNumbers readFile(info_array_with_verbal_commands* array_vb_cmd, const char* file_name);
ErrorNumbers writeCommands(info_array_with_commands array_nl_cmd, const char* file_name);
ErrorNumbers textProcessing(info_array_with_verbal_commands* array_vb_cmd);

#endif // TEXTHANDLER_H
