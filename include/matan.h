/** @file
    @brief Matan type , it`s parsing and general tasks
*/

#ifndef CLIENT_MATAN_H
#define CLIENT_MATAN_H

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
    @struct matan
    @brief defines a tasks matan type
*/
typedef struct {
    char name[100];
    int id;
} matan;

/**
    @brief Parsing all matan structures into json
    @param list - default list of matan structures
    @returns json string
*/
char * parseAllJson(List * list);

/**
    @brief Parsing matan structures into json
    @param mat - default list of matan structures
    @param str - user parametric request
    @returns json string
*/
char * parseMatanRequest(char * str , List * mat);

/**
    @brief Parsing matan structures into json
    @param mat - default list of matan structures
    @param str - user parametric request
    @returns json string
*/
char * parseIdRequest(char * str , List * mat);

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
char * Default();

#endif
