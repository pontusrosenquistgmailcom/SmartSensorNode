#include <stdio.h>
#include <stdlib.h>

#include "tcp/clienttoserver.h"
#include "storage/storage.h"
#include "httpbuilder/httpbuilder.h"
#include "measure/measure.h"
#include "ssn.h"

char* build_http_payload(void* _Context) {
    Storage* storage = (Storage*)_Context;
    httpbuilder_build(storage);
    return storage->http_post_string;
}

int ssn_run_client(Storage* _Storage){
    int keep_looping = 1;
    while(keep_looping == 1) {
    char input;
    printf("Select an option:\n1. Enter new measurement\n2. Display stored data\n3. Send to server and exit\n\nOption: ");

    scanf("%c", &input);

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    switch(input){
        case '1':
            measure_new_measurement(_Storage);
            break;
        case '2':
            storage_print_all_data(_Storage);
            break;
        case '3':
        clienttoserver_send_and_receive(SERVER, PORT, build_http_payload, _Storage);
        keep_looping = 0;
            break;
        default:
            break;
        }

    }
    return 0;
}