/*
 Created by felhr (felhr85@gmail.com)
 */

#include <stdio.h>

void print_help()
{
    printf("UsbTool v 0.1\n");
    printf("Created by: Felipe Herranz (felhr85@gmail.com)\n");
    printf("\n");
    printf("List of commands:\n");
    printf("-hd: Host to device\n");
    printf("-dh: Device to host\n");
    printf("-st: Standard request\n");
    printf("-cl: Class request\n");
    printf("-ve: Vendor request\n");
    printf("-re: Reserved request\n");
    printf("-de: Device recipient\n");
    printf("-in: Interface recipient\n");
    printf("-en: Endpoint recipient\n");
    printf("-h: Help\n");
    printf("-l: List devices\n");
    
}