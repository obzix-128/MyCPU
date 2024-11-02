#ifndef COMPILE_H
#define COMPILE_H

#include "Assembler.h"
#include "../include/Commands.h"
#include "../include/SkipSpaces.h"

ErrorNumbers assemblingCommands(info_array_with_commands* array_nl_cmd,
                       info_array_with_verbal_commands array_vb_cmd);
ErrorNumbers doFixup(info_array_with_commands* array_nl_cmd, stack_info* fixup,
                     labels_info* lables_for_assembler, const int NUMBER_OF_LABELS);

#endif // COMPILE_h
