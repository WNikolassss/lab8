/** @file
    @brief Request type and its parsing
*/

#ifndef REQUEST_H
#define REQUEST_H

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
    @struct Request
    @brief defines a Request data type
*/

typedef struct {
    char command[100];
    char data[100];
} Request;

/**
    @brief Parsing string into Request structure
    @param msgStr - user request
    @returns parsed request type from string
*/
Request parseRequest(const char * msgStr);

/**
    @brief Printing Request structure
    @param req - request for print
*/
void printRequest(Request * req);

/**
    @brief Parsing user string request into standart Http request
    @param msgStr - non http string
*/
void parseHttpRequest(const char * msgStr);


#endif
