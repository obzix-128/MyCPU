#ifndef GENERALINCLUDE_H
#define GENERALINCLUDE_H

const int _SIGNATURE_ = 1482310223;
const int _ASSEMBLER_VERSION_ = 9;

enum CommandNumber{
    PUSH_COMMAND = 1,
    POP_COMMAND  = 2,
    OUT_COMMAND  = 3,
    DUMP_COMMAND = 4,
    HLT_COMMAND  = 5,
    IN_COMMAND   = 6,
    ADD_COMMAND  = 7,
    SUB_COMMAND  = 8,
    MUL_COMMAND  = 9,
    DIV_COMMAND  = 10,
    SQRT_COMMAND = 11,
    SIN_COMMAND  = 12,
    COS_COMMAND  = 13,
    JMP_COMMAND  = 14,
    JB_COMMAND   = 15,
    CALL_COMMAND = 16,
    RET_COMMAND  = 17,
    PRNT_COMMAND = 18,
    JE_COMMAND   = 19,
    SQR_COMMAND  = 20
};

enum ErrorNumbers{
    _NO_ERROR           = 0,
    _STAT_ERROR         = -1,
    _OPEN_ERROR         = 2,
    _CALLOC_ERROR       = 3,
    _COMMAND_LIM_ERROR  = 4,
    _SYNTAXIS_ERROR     = 5,
    _LABELS_LIM_ERROR   = 6,
    _SIGNATURE_ERROR    = 7,
    _REGISTER_LIM_ERROR = 8,
    _RAM_LIM_ERROR      = 9,
    _FILE_NAME_ERROR    = 10,
    _NULL_ADDRESS_ERROR = 11,
    _CHECK_FOUND_ERROR  = 12,
    _SIZE_COMMAND_ERROR = 13
};

enum MeaningBit{
    TURN_ON_IMMED    = 32,
    TURN_ON_REGISTERS = 64,
    TURN_ON_RAM       = 128,
    ONLY_COMMAND      = 31,
    ONLY_MARKERS      = 224
};

struct labels_info {
    int label_address;
    char label_name[11];
};

const unsigned int _SIZE_OF_THE_ARRAY_WITH_COMMANDS = 512;
const unsigned int _NUMBER_OF_REGISTERS = 9;

#endif // GENERALINCLUDE_H
