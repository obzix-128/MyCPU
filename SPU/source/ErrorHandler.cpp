#include "../include/ErrorHandler.h"


ErrorNumbers errorHandler(ErrorNumbers error)
{
    switch(error)
    {
        case _NO_ERROR:
        {
            fprintf(stderr, "No errors were found\n");
            break;
        }
        case _STAT_ERROR:
        {
            fprintf(stderr, "ERROR: stat\n");
            break;
        }
        case _OPEN_ERROR:
        {
            fprintf(stderr, "ERROR: File not open\n");
            break;
        }
        case _CALLOC_ERROR:
        {
            fprintf(stderr, "ERROR: calloc\n");
            break;
        }
        case _COMMAND_LIM_ERROR:
        {
            fprintf(stderr, "ERROR: Increase the limit of commands\n");
            break;
        }
        case _SYNTAXIS_ERROR:
        {
            fprintf(stderr, "ERROR: Syntaxis error\n");
            break;
        }
        case _LABELS_LIM_ERROR:
        {
            fprintf(stderr, "ERROR: Increase the limit of labels\n");
            break;
        }
        case _SIGNATURE_ERROR:
        {
            fprintf(stderr, "ERROR: Invalid signature or version\n");
            break;
        }
        case _REGISTER_LIM_ERROR:
        {
            fprintf(stderr, "ERROR: Increase the limit of registers\n");
            break;
        }
        case _RAM_LIM_ERROR:
        {
            fprintf(stderr, "ERROR: Going beyond RAM\n");
            break;
        }
        case _FILE_NAME_ERROR:
        {
            fprintf(stderr, "ERROR: The file name is not specified\n");
            break;
        }
        default:
        {
            fprintf(stderr, "Unknown error\n");
            break;
        }
    }
    return _NO_ERROR;
}

