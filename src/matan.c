#include "matan.h"

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


char * matan_getName(matan * self){
    return self->name;
}

int matan_getId(matan * self){
    return self->id;
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

char * parseIdRequest(char * str , List * mat){
    int n = 2;
    while(str[n] != '/') n++;
    int j = 0;
    int i = 0;
    char * buffer = (char*)malloc(sizeof(char));

    for(i = n+1, j = 0; i < strlen(str); i++, j++){
        buffer[j] = str[i];
    }
    buffer[j] = '\0';

    if(atoi(buffer) > List_count(mat)){
        return "404 Not found";
    }

    json_t * arr = json_array();
    json_t * json = json_object();

    json_object_set_new(json, "name", json_string(matan_getName(List_get(mat, atoi(buffer)))));
    json_object_set_new(json, "id", json_integer(matan_getId(List_get(mat, atoi(buffer)))));

    json_array_append(arr, json);

    char * jsonString = json_dumps(arr, JSON_INDENT(3));

    free(buffer);
    json_decref(arr);
    return jsonString;
}

char * parseMatanRequest(char * str , List * mat){
    int n = 0;
    while(str[n] != '?') n++;

    int j = 0;
    int i = 0;
    char * key = (char*)malloc(sizeof(char));

    for(i = n+1, j = 0; i < strlen(str); i++, j++){
        if(str[i] == '='){
            break;
        }
        key[j] = str[i];
    }
    key[j] = '\0';

    puts(key);

    i++;
    char * value = (char*)malloc(sizeof(char));
    for(j = 0; i < strlen(str); i++, j++){
        value[j] = str[i];
    }
    value[j] = '\0';

    puts(value);
    printf("%d\n",atoi(value));

    if(strcmp(key , "name") == 0) {
        json_t * arr = json_array();

        for(int z = 0; z < List_count(mat); z++){
            if(strstr(matan_getName(List_get(mat, z)) , value) != NULL){
                json_t *json = json_object();

                json_object_set_new(json, "name", json_string(matan_getName(List_get(mat, z))));
                json_object_set_new(json, "id", json_integer(matan_getId(List_get(mat, z))));

                json_array_append(arr, json);
            }
        }

        char * jsonString = json_dumps(arr, JSON_INDENT(3));

        json_decref(arr);
        return jsonString;

    }else if(strcmp(key , "id") == 0){
        json_t * arr = json_array();
        json_t * json = json_object();

        json_object_set_new(json, "name", json_string(matan_getName(List_get(mat, atoi(value)))));
        json_object_set_new(json, "id", json_integer(matan_getId(List_get(mat, atoi(value)))));

        json_array_append(arr, json);

        char * jsonString = json_dumps(arr, JSON_INDENT(3));

        json_decref(arr);
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

char * Default(){
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
            json_t *json = json_object();

            json_object_set_new(json, "str", json_string(List_get(mat, i)));

            json_array_append(arr, json);
        }
    }
    char *jsonString = json_dumps(arr, JSON_INDENT(3));

    json_decref(arr);

    return jsonString;
}