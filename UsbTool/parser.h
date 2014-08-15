/*
 Created by felhr (felhr85@gmail.com)
 */

#ifndef usbtool_parser_h
#define usbtool_parser_h

/* Parsing commands:
 * -hd: Host to device
 * -dh: Device to host
 * -st: Standard
 * -cl: Class
 * -ve: Vendor
 * -re: Reserved
 * -de: Device
 * -in: Interface
 * -en: Endpoint
 * -h: Help
 * -tp: Test Parser
 */

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

typedef struct UsbParser
{
    /*
     0: Not activated   1: Activated
    */
    
    /* Direction */
    int host2device;
    int device2host;
    
    /* Type  */
    int standard_req;
    int class_req;
    int vendor_req;
    int reserved_req;
    
    /* Recipient  */
    int device;
    int endpoint;
    int interface;
    
    /* Test */
    int test_parser;
    
    /* Help */
    int help;
    
}UsbParser;

int parse_commands(UsbParser* parser, int argc, const char * argv[]);
void free_parser(UsbParser* parser);

#endif
