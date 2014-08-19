/*
Created by felhr (felhr85@gmail.com)
*/

#include <stdio.h>
#include "parser.h"
#include "error.h"
#include "testparser.h"

int main(int argc, const char * argv[])
{
    UsbParser* parser;
    int status = parse_commands(&parser, argc, argv);
    
    if(status == OK_PARAMS) // parsed valid data
    {
        if(test_selected(parser)) // test parser
        {
            print_parsed_data(parser);

        }else if(help_selected(parser)) // show help
        {
            
        }else if(0) // TO-DO List usb devices
        {
            // TO-DO USB Stuff
        }else
        {
            
        }
    }else
    {
        print_parsing_error(status);
    }
    
    return 0;
}

