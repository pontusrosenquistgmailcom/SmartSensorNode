
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/strdup.h"
#include "storage.h"



int storage_init(Storage* _Storage){

    storage_add_to_local_list(_Storage, "2025-09-14 13:15:35", "22.5", DEVICE_ID);
    storage_add_to_local_list(_Storage, "2025-10-30 15:08:50", "14.7", DEVICE_ID);
    storage_add_to_local_list(_Storage, "2025-11-04 00:10:10", "4.2", DEVICE_ID);

    return 0;
}

int storage_add_to_local_list(Storage* _Storage, char* _Time, char* _Temp, char* _DeviceID){
    ListItem* new_item = (ListItem*)malloc(sizeof(ListItem));
    memset(new_item, 0, sizeof(ListItem));
    new_item->time = strdup(_Time);

            char tempstr[64] = {0};
        sprintf(tempstr, "%s °C", _Temp);

    new_item->temp = strdup(tempstr);
    new_item->device_id = strdup(_DeviceID);
    new_item->next = NULL;

    if(_Storage->next == NULL)
    {
        _Storage->next = new_item;
        return 0;
    }
    else
    {
        ListItem* last_item = _Storage->next;
        while(last_item->next)
            last_item = last_item->next;
        last_item->next = new_item;
        return 0;
    }

    return 1;
}

int storage_print_all_data(Storage* _Storage){

    ListItem* current_item = _Storage->next;

    while(current_item != NULL)
    {
        printf("Time: %s\n", current_item->time);
        printf("Temp: %s °C\n", current_item->temp);
        printf("Device: %s\n\n", current_item->device_id);
        current_item = current_item->next;
    }

    return 0;
}

void storage_dispose_items(Storage* _Storage){

    if(_Storage->next == NULL)
        return;
    
    ListItem* current_item = _Storage->next;

    while(current_item != NULL)
    {   
        ListItem* next_item = current_item->next;
        free(current_item->time);
        free(current_item->temp);
        free(current_item->device_id);
        free(current_item);
        current_item = next_item;
    }
}

void storage_destory_storage(Storage* _Storage){
    
    if(_Storage == NULL)
        return;
    
    storage_dispose_items(_Storage);

    if(_Storage->http_post_string != NULL)
        free(_Storage->http_post_string);
    
    free(_Storage);
}
