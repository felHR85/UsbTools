/*
 Created by felhr (felhr85@gmail.com)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

static void allocate_parser(UsbParser* parser)
{
    if(parser == NULL)
        parser = malloc(sizeof(UsbParser));
}

static void init_parser(UsbParser* parser)
{
    parser->host2device = 0;
    parser->device2host = 0;
    parser->standard_req = 0;
    parser->class_req = 0;
    parser->vendor_req = 0;
    parser->reserved_req = 0;
    parser->device = 0;
    parser->endpoint = 0;
    parser->interface = 0;
    parser->test_parser = 0;
    parser->help = 0;
}


static int hasDirection(UsbParser* parser)
{
    if(parser->host2device == 0 && parser->device2host == 0)
        return 0;
    else
        return 1;
}

static int hasType(UsbParser* parser)
{
    if(parser->standard_req == 0 && parser->class_req == 0 && parser->vendor_req == 0 && parser->reserved_req == 0 )
        return 0;
    else
        return 1;
}

static int hasRecipient(UsbParser* parser)
{
    if(parser->device == 0 && parser->endpoint == 0 && parser->interface == 0)
         return 0;
    else
        return 1;
}

static int hasTest(UsbParser* parser)
{
    if(parser->test_parser == 0)
        return 0;
    else
        return 1;
}

static int hasHelp(UsbParser* parser)
{
    if(parser->help == 0)
        return 0;
    else
        return 1;
}


static int check_parameters_validity(UsbParser* parser)
{
    if(!hasHelp(parser) && hasDirection(parser) == 0)
    {
        return NO_DIR;
    }else if(!hasHelp(parser) && hasType(parser) == 0)
    {
        return NO_TYPE;
    }else if(!hasHelp(parser) && hasRecipient(parser) == 0)
    {
        return NO_RECIPIENT;
    }
    return 0;
}


int parse_commands(UsbParser* parser, int argc, const char * argv[])
{
    allocate_parser(parser);
    init_parser(parser);
    
    int commands = argc - 1;
    
    for(int i=1;i<=commands-1;i++)
    {
        if(strcmp(HOST_TO_DEVICE, argv[i]) == 0)
        {
            if(!hasDirection(parser))
            {
                parser->host2device = 1;
            }
            else
            {
                free_parser(parser);
                return REPEATED_VALUE;
            }
            
        }else if(strcmp(DEVICE_TO_HOST, argv[i]) == 0)
        {
            if(!hasDirection(parser))
            {
                parser->device2host = 1;
            }else
            {
                free_parser(parser);
                return REPEATED_VALUE;
            }
        }else if(strcmp(STANDARD, argv[i]) == 0)
        {
            if(!hasType(parser))
            {
                parser->standard_req = 1;
            }else
            {
                free_parser(parser);
                return REPEATED_VALUE;
            }
        }else if(strcmp(CLASS, argv[i]) == 0)
        {
            if(!hasType(parser))
            {
                parser->class_req = 1;
            }else
            {
                free_parser(parser);
                return REPEATED_VALUE;
            }

        }else if(strcmp(VENDOR, argv[i]) == 0)
        {
            if(!hasType(parser))
            {
                parser->vendor_req = 1;
            }else
            {
                free_parser(parser);
                return REPEATED_VALUE;
            }
        }else if(strcmp(RESERVED, argv[i]) == 0)
        {
            if(!hasType(parser))
            {
                parser->reserved_req= 1;
            }else
            {
                free_parser(parser);
                return REPEATED_VALUE;
            }
            
        }else if(strcmp(DEVICE, argv[i]))
        {
            if(!hasRecipient(parser))
            {
                parser->device = 1;
            }else
            {
                free_parser(parser);
                return REPEATED_VALUE;
            }
        }else if(strcmp(ENDPOINT, argv[i]))
        {
            if(!hasRecipient(parser))
            {
                parser->endpoint = 1;
            }else
            {
                free_parser(parser);
                return REPEATED_VALUE;
            }
        }else if(strcmp(INTERFACE, argv[i]))
        {
            if(!hasRecipient(parser))
            {
                parser->interface = 1;
            }else
            {
                free_parser(parser);
                return REPEATED_VALUE;
            }
        }else if(strcmp(TEST_PARSER, argv[i]))
        {
            if(!hasTest(parser))
            {
                parser->test_parser = 1;
               
            }else
            {
                free_parser(parser);
                return REPEATED_VALUE;
            }
        }else if(strcmp(HELP, argv[i]))
        {
            if(!hasDirection(parser) && !hasType(parser) && !hasRecipient(parser) && !hasTest(parser))
            {
                parser->help = 1;
                return 0;
            }else
            {
                free_parser(parser);
                return REPEATED_VALUE;
            }
        }else
        {
            free_parser(parser);
            return INVALID;
        }
    }
    
    return check_parameters_validity(parser);
}

void free_parser(UsbParser* parser)
{
    if(parser != NULL)
        free(parser);
}

int help_selected(UsbParser* parser)
{
    return parser->help;
}
