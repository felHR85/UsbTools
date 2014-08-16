/*
Created by felhr (felhr85@gmail.com)
*/

#include <stdio.h>
#include "parser.h"
#include "testparser.h"

int main(int argc, const char * argv[])
{
    UsbParser* parser;
    int status = parse_commands(parser, argc, argv);
    if(status == 0)
    {
        if(test_selected(parser)) // test parser
        {
            print_parsed_data(parser);

        }else if(help_selected(parser)) // show help
        {
            
        }else 
        {
            // TO-DO USB Stuff
        }
    }
    return 0;
}

