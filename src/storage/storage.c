
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/strdup.h"
#include "storage.h"

int LL_init(LocalList* _LL){

    _LL = (LocalList*)malloc(sizeof(LocalList));
    memset(_LL, 0, sizeof(LocalList));

    LL_add_to_local_list(_LL, "2025-09-15_14:35", 22.5, 9902347);
    LL_add_to_local_list(_LL, "2025-10-17_07:59", 14.7, 9902347);
    LL_add_to_local_list(_LL, "2025-11-04_00:10", 4.2, 9902347);

    /*LL_print_all_data(_LL);*/

    return 0;
}

int LL_add_to_local_list(LocalList* _LL, char* _Time, float _Temp, int _DeviceID){
    LocalListItem* new_item = (LocalListItem*)malloc(sizeof(LocalListItem));
    memset(new_item, 0, sizeof(LocalListItem));
    new_item->time = strdup(_Time);
    new_item->temp = _Temp;
    new_item->device_id = _DeviceID;
    new_item->next = NULL;

    if(_LL->next == NULL)
    {
        _LL->next = new_item;
        return 0;
    }
    else
    {
        LocalListItem* last_item = _LL->next;
        while(last_item->next)
            last_item = last_item->next;
        last_item->next = new_item;
        return 0;
    }

    return 1;
}

int LL_print_all_data(LocalList* _LL){

    LocalListItem* current_item = _LL->next;

    while(current_item != NULL)
    {
        printf("Time: %s\n", current_item->time);
        printf("Temp: %.2f\n", current_item->temp);
        printf("Device: %d\n\n", current_item->device_id);
        current_item = current_item->next;
    }

    return 0;
}

