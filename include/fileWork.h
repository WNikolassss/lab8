//
// Created by nikolassss on 01.06.17.
//

#ifndef CLIENT_FILEWORK_H
#define CLIENT_FILEWORK_H


#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <jansson.h>
#include <list.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <matan.h>
#include <time.h>

/**
    @brief file reader
    @returns json string with file data
*/
char * file();

/**
    @brief file reader and task
    @returns json string with file data task
*/
char * fileData();

/**
    @brief creating default server output
    @returns json string with default server parameteres
*/
char * defaultResponse();

#endif //CLIENT_FILEWORK_H
