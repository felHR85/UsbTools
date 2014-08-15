//
//  parser.c
//  usbtool
//
//  Created by Felipe Herranz Rabanal on 15/08/14.
//  Copyright (c) 2014 Felipe Herranz Rabanal. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

static void initialize_parser(UsbParser* parser)
{
    if(parser == NULL)
    {
        parser = malloc(sizeof(UsbParser));
    }
}


void parse_commands(UsbParser* parser, int argc, const char * argv[])
{
    initialize_parser(parser);
    
    int commands = argc - 1;
    
    for(int i=1;i<=commands-1;i++)
    {
        if(strcmp(HOST_TO_DEVICE, argv[i]))
        {
            parser->host2device = 1;
        }
    }
}

void free_parser(UsbParser* parser)
{
    if(parser != NULL)
    {
        free(parser);
    }
}
