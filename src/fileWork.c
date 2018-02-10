#include "fileWork.h"

int countSymbols(char * str){
    int count = 0;
    while(str[count] != '\0'){
        count++;
    }
    return count;
}

char * readAllText(const char * fileName){
    FILE *file = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int c;

    if (file == NULL) return NULL; //could not open file
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code = malloc(f_size);

    while ((c = fgetc(file)) != EOF) {
        code[n++] = (char)c;
    }

    code[n] = '\0';

    return code;
}


char * defaultResponse(){
    json_t * arr = json_array();
    json_t * json = json_object();

    time_t t;
    t=time(NULL);

    json_object_set_new(json, "title", json_string("MyServer"));
    json_object_set_new(json, "developer", json_string("Mykola_KP62"));
    json_object_set_new(json, "time", json_string(ctime(&t)));

    json_array_append(arr, json);

    char * jsonString = json_dumps(arr, JSON_INDENT(3));

    json_decref(arr);
    return jsonString;
}


char * fileData(){
    List * mat = List_new();

    int i = 0;
    char temp[800];

    strcpy(temp,readAllText("data"));

    char *sp;

    sp = strtok(temp , " ");
    while (sp) {
        List_add(mat , sp);
        sp = strtok(NULL, " ");
    }

    json_t *arr = json_array();

    for (i = 0; i < List_count(mat); i++) {
        if( (i+1) % 2 == 0) {
            json_array_append(arr, json_string(List_get(mat, i)));
        }
    }
    char *jsonString = json_dumps(arr, JSON_INDENT(3));

    json_decref(arr);

    return jsonString;
}


char * file(){
    json_t * arr = json_array();
    json_t * json = json_object();

    json_object_set_new(json, "name", json_string("data"));
    json_object_set_new(json, "size", json_integer(countSymbols(readAllText("data"))));
    json_object_set_new(json, "data", json_string(readAllText("data")));

    json_array_append(arr, json);

    char * jsonString = json_dumps(arr, JSON_INDENT(3));

    json_decref(arr);
    return jsonString;
}