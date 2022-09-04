#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 10000 // max characters per row
#define MAX_LINE_NUMBER 10000 // max rows
#include "request.c"
#include "parser.c"

extern int curlInto(char *buffer, char * command);
extern char * readAfter(char *string, char * substr);

int main(int argc, char **argv)
{
    // if(argc < 1)
    // {
    //     printf("...No address specified...");
    //     return(-1);
    // }
    
    // allocate extra large buffer for the request
    char * _intputBuffer = malloc(MAX_LINE_LENGTH * MAX_LINE_NUMBER);

    curlInto(_intputBuffer, "curl http://example.com/");

    // allocate the correctly-sized buffer
    char buffer[strlen(_intputBuffer)];
    strcpy(buffer, _intputBuffer);

    // free the old, bigger, buffer
    free(_intputBuffer);

    char *BODY = readAfter(buffer, "<html>");
    char *ENDBODY = readAfter(buffer, "</html>") - 7;
    *ENDBODY = 0; // terminate at the end of the body

    printf("%s", BODY);
}