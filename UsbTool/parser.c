/*
 Created by felhr (felhr85@gmail.com)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"


const char HOST_TO_DEVICE[] = "-hd";
const char DEVICE_TO_HOST[] = "-dh";
const char STANDARD[] = "-st";
const char CLASS[] = "-cl";
const char VENDOR[] = "-ve";
const char RESERVED[] = "-re";
const char DEVICE[] = "-de";
const char INTERFACE[] = "-in";
const char ENDPOINT[] = "-en";
const char TEST_PARSER[] = "-tp";
const char HELP[] = "-h";

const int OK_PARAMS = 0;
const int INVALID = -1;
const int REPEATED_VALUE = -2;
const int NO_DIR = -3;
const int NO_TYPE = -4;
const int NO_RECIPIENT = -5;
const int NO_ARGUMENTS = -6;

static void init_parser(UsbParser** parser)
{
    if(parser == NULL)
    {
        *parser = (UsbParser*) malloc(sizeof(UsbParser));
        (*parser)->host2device = 0;
        (*parser)->device2host = 0;
        (*parser)->standard_req = 0;
        (*parser)->class_req = 0;
        (*parser)->vendor_req = 0;
        (*parser)->reserved_req = 0;
        (*parser)->device = 0;
        (*parser)->endpoint = 0;
        (*parser)->interface = 0;
        (*parser)->test_parser = 0;
        (*parser)->help = 0;
    }
}


static int has_direction(UsbParser* parser)
{
    if(parser->host2device == 0 && parser->device2host == 0)
        return 0;
    else
        return 1;
}

static int has_type(UsbParser* parser)
{
    if(parser->standard_req == 0 && parser->class_req == 0 && parser->vendor_req == 0 && parser->reserved_req == 0 )
        return 0;
    else
        return 1;
}

static int has_recipient(UsbParser* parser)
{
    if(parser->device == 0 && parser->endpoint == 0 && parser->interface == 0)
         return 0;
    else
        return 1;
}

static int has_test(UsbParser* parser)
{
    if(parser->test_parser == 0)
        return 0;
    else
        return 1;
}

static int has_help(UsbParser* parser)
{
    if(parser->help == 0)
        return 0;
    else
        return 1;
}


static int check_parameters_validity(UsbParser* parser)
{
    if(!has_help(parser) && has_direction(parser) == 0)
    {
        return NO_DIR;
    }else if(!has_help(parser) && has_type(parser) == 0)
    {
        return NO_TYPE;
    }else if(!has_help(parser) && has_recipient(parser) == 0)
    {
        return NO_RECIPIENT;
    }
    return OK_PARAMS;
}


int parse_commands(UsbParser* parser, int argc, const char * argv[])
{
    init_parser(&parser);
    
    if(argc == 1)
        return NO_ARGUMENTS;
    
    int commands = argc - 1;
    
    for(int i=1;i<=commands-1;i++)
    {
        if(strcmp(HOST_TO_DEVICE, argv[i]) == 0)
        {
            if(!has_direction(parser))
            {
                parser->host2device = 1;
            }
            else
            {
                free_parser(&parser);
                return REPEATED_VALUE;
            }
            
        }else if(strcmp(DEVICE_TO_HOST, argv[i]) == 0)
        {
            if(!has_direction(parser))
            {
                parser->device2host = 1;
            }else
            {
                free_parser(&parser);
                return REPEATED_VALUE;
            }
        }else if(strcmp(STANDARD, argv[i]) == 0)
        {
            if(!has_type(parser))
            {
                parser->standard_req = 1;
            }else
            {
                free_parser(&parser);
                return REPEATED_VALUE;
            }
        }else if(strcmp(CLASS, argv[i]) == 0)
        {
            if(!has_type(parser))
            {
                parser->class_req = 1;
            }else
            {
                free_parser(&parser);
                return REPEATED_VALUE;
            }

        }else if(strcmp(VENDOR, argv[i]) == 0)
        {
            if(!has_type(parser))
            {
                parser->vendor_req = 1;
            }else
            {
                free_parser(&parser);
                return REPEATED_VALUE;
            }
        }else if(strcmp(RESERVED, argv[i]) == 0)
        {
            if(!has_type(parser))
            {
                parser->reserved_req= 1;
            }else
            {
                free_parser(&parser);
                return REPEATED_VALUE;
            }
            
        }else if(strcmp(DEVICE, argv[i]))
        {
            if(!has_recipient(parser))
            {
                parser->device = 1;
            }else
            {
                free_parser(&parser);
                return REPEATED_VALUE;
            }
        }else if(strcmp(ENDPOINT, argv[i]))
        {
            if(!has_recipient(parser))
            {
                parser->endpoint = 1;
            }else
            {
                free_parser(&parser);
                return REPEATED_VALUE;
            }
        }else if(strcmp(INTERFACE, argv[i]))
        {
            if(!has_recipient(parser))
            {
                parser->interface = 1;
            }else
            {
                free_parser(&parser);
                return REPEATED_VALUE;
            }
        }else if(strcmp(TEST_PARSER, argv[i]))
        {
            if(!has_test(parser))
            {
                parser->test_parser = 1;
               
            }else
            {
                free_parser(&parser);
                return REPEATED_VALUE;
            }
        }else if(strcmp(HELP, argv[i]))
        {
            if(!has_direction(parser) && !has_type(parser) && !has_recipient(parser) && !has_test(parser))
            {
                parser->help = 1;
                return 0;
            }else
            {
                free_parser(&parser);
                return REPEATED_VALUE;
            }
        }else
        {
            free_parser(&parser);
            return INVALID;
        }
    }
    
    return check_parameters_validity(parser);
}

void free_parser(UsbParser** parser)
{
    if((*parser) != NULL)
        free((*parser));
}

int help_selected(UsbParser* parser)
{
    return parser->help;
}
