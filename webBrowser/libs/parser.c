typedef struct
{
    char type;
    char *text;
} htext_t;


#define subSection(offset, ldbuff, start_str, finish_str, bufname)                      \
    char *(ldbuff##_START) = readAfter(bufname, start_str, offset);                     \
    char *(ldbuff##_END) = readAfter(bufname, finish_str, offset) - strlen(finish_str); \
    *(ldbuff##_END) = 0;                                                                \
    char(ldbuff)[strlen(ldbuff##_START)];                                               \
    strcpy(ldbuff, ldbuff##_START);                                                     \
    *(ldbuff##_END) = '<';

// load the format NOT CORRECT
int getPageLayout(char *outBuffer, char *inputBuffer)
{
    char index = 0;
    while(*inputBuffer != 0)
    {
        if(*inputBuffer == '<' && *(inputBuffer+1) != '/')
        {
            outBuffer[index++] = *(inputBuffer+2);
        }
        inputBuffer++;
    }
    return index;
}

//returns right after a substring
extern char *readAfter(char *string, char *substr, int index)
{
    int sublen = strlen(substr);
    int sind = 0;

    while (*string != 0)
    {
        if (substr[sind] == *string)
        {
            if (sind == sublen - 1)
            { // if match return beginning of match
                index--;
                if (index == 0)
                {
                    return string + 1;
                }
            }
            else // next char to compare
            {
                sind++;
            }
        }
        else
        {
            sind = 0;
        }
        string++;
    }
    return 0;
}


int loadStyleBuffer(char *destBuffer[], char *sourceBuffer, char *start_style, char *fin_style)
{
    int load_ind = 0;
    char * startPointer;
    long finStart = strlen(fin_style);
    char * finPointer;
    char * allocated;


    for(int i = 1; i > 0; i++) {
        startPointer = readAfter(sourceBuffer, start_style, i);
        if(startPointer == 0) return i;
        finPointer = readAfter(sourceBuffer, fin_style, i) - finStart;
        g_print("%s %p end %p\n", start_style, startPointer, finPointer);
        *finPointer = 0;

        // load the substring into a new buffer for it
        allocated = (char*)malloc(strlen(startPointer));
        strcpy(allocated, startPointer);

        g_print("index %i, data: %s\n", i, allocated);
        destBuffer[load_ind++] = allocated; 

        *finPointer = '<';
    }
    return 0;


    // load each substring into the array 
    // while ((startPointer = readAfter(sourceBuffer, start_style, string_ind)) != 0) {
    //     // find ending
    //     finPointer = readAfter(sourceBuffer, fin_style, string_ind++) - lenFin;
    //     *finPointer = 0;

    //     // load the substring into a new buffer for it
    //     allocated = (char*)malloc(strlen(startPointer));
    //     strcpy(allocated, startPointer);

    //     g_print("index %i, data: %s\n", string_ind, allocated);
    //     destBuffer[load_ind++] = allocated; 

    //     *finPointer = '<';
    // }
}