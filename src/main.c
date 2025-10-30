#include <stdio.h>
#include <stdlib.h>

#include "storage/storage.h"
#include "ssn.h"


int main(){
    
    Storage* storage = (Storage*)malloc(sizeof(Storage));
    memset(storage, 0, sizeof(Storage));
    
    /* 1x preprgogrammed data entry */
    storage_init(storage);

    ssn_run_client(storage);

    storage_destory_storage(storage);

    return 0;
}