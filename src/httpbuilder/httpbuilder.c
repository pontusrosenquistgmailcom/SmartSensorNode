
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
    int i = 1;
    while(current_item != NULL)
    {
        /*
        printf("Hello from inside while loop in httpbuilder\n\n");

        printf("Time: %s\n", current_item->time);
        printf("Temp: %.2f\n", current_item->temp);
        printf("Device: %d\n\n", current_item->device_id);
        */
        cJSON_AddItemToArray(cjson_measurements, cjson_data = cJSON_CreateObject());
        cJSON_AddItemToObject(cjson_data, "time", cJSON_CreateString(current_item->time));
        cJSON_AddNumberToObject(cjson_data, "temperature", current_item->temp);
        cJSON_AddNumberToObject(cjson_data, "UUID", current_item->device_id);
        
        current_item = current_item->next;
    }


    char http_blob[8192];
    
    sprintf(http_blob, "POST /#/HTTP_Methods/post_post HTTP/1.1\r\n");

    _Storage->json_report_string = cJSON_Print(cjson_root);

    

    cJSON_Delete(cjson_root);

    return 0;
}