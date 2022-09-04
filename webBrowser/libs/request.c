#ifndef MAX_LINE_LENGTH
#define MAX_LINE_LENGTH 100 // max characters per row
#endif

#ifndef MAX_LINE_NUMBER
#define MAX_LINE_NUMBER 100000 // max rows
#endif

int system(const char *command);

extern int curlInto(char *buffer, char * command)

{ 
    FILE *fp;
    char buf[MAX_LINE_LENGTH];

    if ((fp = popen(command, "r")) == NULL) {
        printf("Error opening pipe!\n");
        return -1;
    }

    char *buffer_at = buffer;

    while (fgets(buf, MAX_LINE_LENGTH, fp) != NULL) {
        strcpy(buffer_at, buf);
        buffer_at += strlen(buf);
    }

    if (pclose(fp)) {
        printf("Command not found or exited with error status\n");
        return -1;
    }

    return 0;
}