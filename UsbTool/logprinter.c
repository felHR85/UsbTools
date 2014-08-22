/*
 Created by felhr (felhr85@gmail.com)
 */

#include <stdio.h>
#include "logprinter.h"

const int OK_RESPONSES = 0;
const int NO_OK_RESPONSES = 1;

void print_responses_log(UsbResponse** responses, int options)
{
    if(options == OK_RESPONSES)
    {
        for(int i=0;i<=255;i++)
        {
            if(responses[i]->response >= 0)
            {
                printf("Response: %d    ", responses[i]->response);
                printf("bmRequestType: %x    ", responses[i]->bm_request_type);
                printf("bRequestType: %x    ", responses[i]->b_request);
                printf("wValue: %x    ", responses[i]->w_value);
                printf("wIndex: %x    ", responses[i]->w_index);
                printf("wLength: %x    ", responses[i]->w_length);
                printf("\n");
            }
        }
    }else if(options == NO_OK_RESPONSES)
    {
        for(int i=0;i<=255;i++)
        {
            if(responses[i]->response < 0)
            {
                printf("Response: %d    ", responses[i]->response);
                printf("bmRequestType: %x    ", responses[i]->bm_request_type);
                printf("bRequestType: %x    ", responses[i]->b_request);
                printf("wValue: %x    ", responses[i]->w_value);
                printf("wIndex: %x    ", responses[i]->w_index);
                printf("wLength: %x    ", responses[i]->w_length);
                printf("\n");
            }
        }
    }
}


void print_list_log(UsbDevice** devices, int options)
{
    int i = 0;
    while(devices[i] != NULL)
    {
        printf("VID: %x    ", devices[i]->id_vendor);
        printf("PID: %x    ", devices[i]->id_product);
        printf("\n");
        i++;
    }
}

