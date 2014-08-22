/*
 Created by felhr (felhr85@gmail.com)
 */

#ifndef usbtool_logprinter_h
#define usbtool_logprinter_h

#include "usbfacade.h"

extern const int OK_RESPONSES;
extern const int NO_OK_RESPONSES;

/* Options:
 * 0= Ok responses
 * 1= No ok Responses
 */
void print_responses_log(UsbResponse** responses, int options);
void print_list_log(UsbDevice** devices, int options);


#endif
