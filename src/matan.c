#include "matan.h"

char * matan_getName(matan * self){
    return self->name;
}

int matan_getId(matan * self){
    return self->id;
}

char * parseIdRequest(char * str , List * mat){
    int n = 2;
    while(str[n] != '/') n++;
    int j = 0;
    int i = 0;
    char * buffer = malloc(sizeof(char) * strlen(str));

    for(i = n+1, j = 0; i < strlen(str); i++, j++){
        buffer[j] = str[i];
    }
    buffer[j] = '\0';

    if(atoi(buffer) >= List_count(mat)){
        return "404 Not found";
    }

    json_t * arr = json_array();
    json_t * json = json_object();

    json_object_set_new(json, "name", json_string(matan_getName(List_get(mat, atoi(buffer)))));
    json_object_set_new(json, "id", json_integer(matan_getId(List_get(mat, atoi(buffer)))));

    json_array_append(arr, json);

    char * jsonString = json_dumps(arr, JSON_INDENT(3));

    json_decref(arr);
    return jsonString;
}

char * parseMatanRequest(char * str , List * mat){
    int n = 0;
    while(str[n] != '?') n++;

    int j = 0;
    int i = 0;

    char * key = malloc(sizeof(char) * strlen(str));
    //char key[100];

    for(i = n+1, j = 0; i < strlen(str); i++, j++){
        if(str[i] == '='){
            break;
        }
        key[j] = str[i];
    }
    key[j] = '\0';
    puts(key);

    i++;
    char * value = malloc(sizeof(char)*strlen(str));
    //char value[100];
    for(j = 0; i < strlen(str); i++, j++){
        value[j] = str[i];
    }
    value[j] = '\0';
    puts(value);

    if(strcmp("name" , key) == 0) {
        json_t * arr = json_array();

        for(int z = 0; z < List_count(mat); z++){
            if(strstr(value , matan_getName(List_get(mat, z))) != NULL){
                json_t *json = json_object();

                json_object_set_new(json, "name", json_string(matan_getName(List_get(mat, z))));
                json_object_set_new(json, "id", json_integer(matan_getId(List_get(mat, z))));

                json_array_append(arr, json);
            }
        }

        char * jsonString = json_dumps(arr, JSON_INDENT(3));

        json_decref(arr);
        free(key);
        free(value);

        return jsonString;

    }else if(strstr("id" , key) != NULL){
        json_t * arr = json_array();
        json_t * json = json_object();

        json_object_set_new(json, "name", json_string(matan_getName(List_get(mat, atoi(value)))));
        json_object_set_new(json, "id", json_integer(matan_getId(List_get(mat, atoi(value)))));

        json_array_append(arr, json);

        char * jsonString = json_dumps(arr, JSON_INDENT(3));

        json_decref(arr);
        free(key);
        free(value);

        return jsonString;
    }
    return "Error : Something went wrong";
}

char * parseAllJson(List * mat) {
    json_t *arr = json_array();

    for (int i = 0; i < List_count(mat); i++) {
        json_t *json = json_object();

        json_object_set_new(json, "name", json_string(matan_getName(List_get(mat, i))));
        json_object_set_new(json, "id", json_integer(matan_getId(List_get(mat, i))));

        json_array_append(arr, json);
    }
    char *jsonString = json_dumps(arr, JSON_INDENT(3));
    json_decref(arr);
    return jsonString;
}

