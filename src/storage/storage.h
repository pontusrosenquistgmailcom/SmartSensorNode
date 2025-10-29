
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/strdup.h"

typedef struct LocalListItem LocalListItem;

typedef struct LocalListItem{
    char* time;
    float temp;
    int device_id;
    
    /* ... */
    LocalListItem* next;
    
} LocalListItem;

typedef struct LocalList{
    LocalListItem* next;
}LocalList;

int LL_init(LocalList* _LL);

int LL_add_to_local_list(LocalList* _LL, char* _Time, float _Temp, int _DeviceID);

int LL_print_all_data(LocalList* _LL);

