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

/* Error codes:
 * 0 == OK
 * 1 == Invalid command
 * 2 == Repeated Value
 * 3 == No direction specified
 * 4 == No Type specified
 * 5 == No Recipient
 *
 */

extern const char HOST_TO_DEVICE[];
extern const char DEVICE_TO_HOST[];
extern const char STANDARD[];
extern const char CLASS[];
extern const char VENDOR[];
extern const char RESERVED[];
extern const char DEVICE[];
extern const char INTERFACE[];
extern const char ENDPOINT[];
extern const char TEST_PARSER[];
extern const char HELP[];

extern const int OK_PARAMS;
extern const int INVALID;
extern const int REPEATED_VALUE;
extern const int NO_DIR;
extern const int NO_TYPE;
extern const int NO_RECIPIENT;
extern const int NO_ARGUMENTS;

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
void free_parser(UsbParser** parser);
int help_selected(UsbParser* parser);
void print_help();

#endif
