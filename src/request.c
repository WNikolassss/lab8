#include "request.h"

Request parseRequest(const char * msgStr) {
    Request req = {
            .command = "",
            .data = ""
    };

    int n = 0;
    while(isalpha(msgStr[n])) n++;

    strncpy(req.command, msgStr, n);
    req.command[n] = '\0';

    int j = 0;
    int i = 0;
    char * buffer = (char*)malloc(sizeof(char));

    for(i = n+1, j = 0; i < strlen(msgStr); i++, j++){
        if(msgStr[i] == ' '){
            break;
        }
        buffer[j] = msgStr[i];
    }

    buffer[j] = '\0';
    strcpy(req.data, buffer);

    return req;
}

void printRequest(Request * req) {
    printf("Request: `%s` `%s`\n",
           req->command,
           req->data);
}

void parseHttpRequest(const char * msgStr) {
    char * str = malloc(sizeof(char) * 150);
    strcat(str , "GET ");
    strcat(str , msgStr);
    strcat(str , " HTTP/1.0");
    strcpy(msgStr , str);
}
