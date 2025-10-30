#ifndef __STORAGE_H__
#define __STORAGE_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/strdup.h"

#define DEVICE_ID "514729"

typedef struct ListItem ListItem;

typedef struct ListItem{
    char* time;
    char* temp;
    char* device_id;
    
    /* ... */
    ListItem* next;
    
} ListItem;

typedef struct Storage{
    ListItem* next;
    char* http_post_string;
    char* server;
}Storage;

int storage_init(Storage* _Storage);

int storage_add_to_local_list(Storage* _Storage, char* _Time, char* _Temp, char* _DeviceID);

int storage_print_all_data(Storage* _Storage);

void storage_dispose_items(Storage* _Storage);

void storage_destory_storage(Storage* _Storage);

#endif /* __STORAGE_H__ */