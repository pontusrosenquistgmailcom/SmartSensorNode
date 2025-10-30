#include <stdio.h>
#include <stdlib.h>

#include "clienttoserver.h"
#include "storage/storage.h"
#include "httpbuilder/httpbuilder.h"

#define DEVICE_ID 514729
#define SERVER "www.httpbin.org"
#define PORT "80"

char* build_http_payload(void* _Context) {
    Storage* storage = (Storage*)_Context;
    return storage->http_post_string;
}

int main(){
    
    /* ########     DUMMY DATA START       ########### 3x data entries in code*/
    Storage* storage = (Storage*)malloc(sizeof(Storage));
    memset(storage, 0, sizeof(Storage));
    storage_init(storage);
    /* ########     DUMMY DATA END       ########### */


    /* build HTTP POST request */

    httpbuilder_build(storage);
    /*printf("contents of storage->json_report:\n%s\n", storage->http_post_string);*/


    /* ########     TCP CLIENT START     ######### */
    clienttoserver_send_and_receive(SERVER, PORT, build_http_payload, storage);

    /* ########     TCP CLIENT END       ######### */
    return 0;
}