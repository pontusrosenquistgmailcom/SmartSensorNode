#include <stdio.h>
#include <stdlib.h>

#include "clienttoserver.h"
#include "storage/storage.h"
#include "httpbuilder/httpbuilder.h"
#include "measure/measure.h"

#define SERVER "www.httpbin.org"
#define PORT "80"

char* build_http_payload(void* _Context) {
    Storage* storage = (Storage*)_Context;
    httpbuilder_build(storage);
    return storage->http_post_string;
}

int main(){
    
    /* 3x preprgogrammed data entries */
    Storage* storage = (Storage*)malloc(sizeof(Storage));
    memset(storage, 0, sizeof(Storage));
    storage_init(storage);

    measure_new_measurement(storage);

    /* connect to server and send stored data with http POST request */
    clienttoserver_send_and_receive(SERVER, PORT, build_http_payload, storage);

  
    storage_destory_storage(storage);

    return 0;
}