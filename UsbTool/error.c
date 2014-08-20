/*
 Created by felhr (felhr85@gmail.com)
 */
#include <stdio.h>
#include "parser.h"

void print_parsing_error(int error)
{
    switch (error)
    {
        case -1: // INVALID
            printf("Invalid command\n");
            break;
        case -2: // REPEATED VALUE
            printf("Repeated value\n");
            break;
        case -3: // NO_DIR
            printf("No direction was specified: Use -hd (host to device) or -dh (device to host)\n");
            break;
        case -4: // NO_TYPE
            printf("No type was specified: Use -st for Standard, -cl for Class, -ve for Vendor or -re for Reserved\n");
            break;
        case -5: // NO_RECIPIENT
            printf("No recipient was specified. Use -de for Device, -in for Interface or -en for endpoint\n");
            break;
        case -6: // NO_ARGUMENTS
            printf("Some arguments are needed. Use -h for Help\n");
            break;
        case -7: // NO_VID_PID
            printf("No vid (vendor identification) or pid (product identification) was supplied\n");
            break;
        case -8: // TOO_ARGUMENTS_HELP
            printf("Help requires one argument: -h\n");
            break;
        case -9: // TOO_ARGUMENTS_LIST
            printf("List requires one argument: -l\n");
            break;
        default:
            printf("A parsing error occurred\n");
            break;
    }
}