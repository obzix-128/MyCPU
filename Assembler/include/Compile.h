#ifndef COMPILE_H
#define COMPILE_H

#include "Assembler.h"
#include "Commands.h"
#include "TextHandler.h"

ErrorNumbers assemblingCommands(info_array_with_commands* array_nl_cmd,
                       info_array_with_verbal_commands* array_vb_cmd);
ErrorNumbers commandProcessing(unsigned int* ip, char* command, const int NUMBER_OF_LABELS,
                               info_array_with_commands* array_nl_cmd,
                               labels_info* lables_for_assembler,
                               info_array_with_verbal_commands* array_vb_cmd, stack_info* fixup);
ErrorNumbers labelProcessing(char* command, const int NUMBER_OF_LABELS, unsigned int* ip,
                             labels_info* lables_for_assembler);
ErrorNumbers doFixup(info_array_with_commands* array_nl_cmd, stack_info* fixup,
                     labels_info* lables_for_assembler, const int NUMBER_OF_LABELS);

#endif // COMPILE_H
