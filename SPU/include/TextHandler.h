#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H

#include "Processor.h"

ErrorNumbers checkVersion(info_array_with_commands_txt* commands);
ErrorNumbers processingAnArrayOfCommands(info_array_with_commands_txt* commands,
                                         info_array_with_commands_code* executable_code);
                                         
#endif //TEXTHANDLER_H
