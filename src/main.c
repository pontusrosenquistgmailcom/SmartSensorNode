#include <stdio.h>
#include <stdlib.h>

#include "clienttoserver.h"
#include "storage/storage.h"
#include "httpbuilder/httpbuilder.h"


#define DEVICE_ID 514729
#define SERVER "142.250.74.132"
#define PORT "80"
/* "142.250.74.132", "80" google.com */

int main(){
    
    printf("Hello world!\n\n");
    
    /* ########     DUMMY DATA START       ########### 3x data entries in code*/

    Storage* storage = (Storage*)malloc(sizeof(Storage));
    memset(storage, 0, sizeof(Storage));
    storage_init(storage);


    /* ########     DUMMY DATA END       ########### */

    /* build HTTP POST request */

    httpbuilder_build(storage);

    printf("contents of storage->json_report:\n%s\n", storage->json_report_string);


    /* ########     TCP CLIENT START     ######### */

    clienttoserver_send_and_receive(SERVER, PORT);

    /* ########     TCP CLIENT END       ######### */
    return 0;
}