#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../cJSON/cJSON.h"
#include "httpbuilder.h"

int httpbuilder_build(Storage* _Storage){

    if(_Storage->next == NULL){
        return -1;
    }

    ListItem* current_item = _Storage->next;

    cJSON* cjson_root = cJSON_CreateObject();
    cJSON* cjson_measurements = cJSON_CreateArray();
    cJSON* cjson_data;

    cJSON_AddItemToObject(cjson_root, "measurements", cjson_measurements);
    /*int i = 1;*/
    while(current_item != NULL)
    {
        cJSON_AddItemToArray(cjson_measurements, cjson_data = cJSON_CreateObject());
        cJSON_AddItemToObject(cjson_data, "time", cJSON_CreateString(current_item->time));
        cJSON_AddNumberToObject(cjson_data, "temperature", current_item->temp);
        cJSON_AddNumberToObject(cjson_data, "UUID", current_item->device_id);
        
        current_item = current_item->next;
    }



    char* json_data_string = cJSON_Print(cjson_root);

    int content_length = strlen(json_data_string);
    
    char* http_blob = (char*)malloc(8192);
    /*
    POST /post HTTP/1.1\r\nHost: www.httpbin.org\r\naccept: application/json\r\nContent-Length: 5\r\n\r\nHello\r\n";
    */
    sprintf(http_blob, "POST /post HTTP/1.1\r\nHost: localhost:80\r\nContent-Length: %i\r\n\r\n%s", content_length, json_data_string);

    _Storage->http_post_string = http_blob;

    cJSON_Delete(cjson_root);
    free(json_data_string);
    return 0;
}