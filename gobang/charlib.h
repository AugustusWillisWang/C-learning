#ifndef CHARLIB
#define CHARLIB


char* DelSpaceAddLog(char* input){
    int a = 0;
    int b = 0;
    char *output = (char *)malloc(sizeof(char) * (strlen(input) + 5));
    while (input[a] != '\n')
    {
        if(input[a]!=' '&&input[a]!=':'){
            output[b] = input[a];
            b++;
        }
        a++;
    }
    output[b++] = '.';
    output[b++] = 'l';
    output[b++] = 'o';
    output[b++] = 'g';
    output[b++] = '\0';
    return output;
}

#endif