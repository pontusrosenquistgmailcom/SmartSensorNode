

#include <stdio.h>
#include <time.h>

#include "../storage/storage.h"
#include "measure.h"

char* GetUserInputChar();
void current_time(char* buffer, size_t buffer_size);

int measure_new_measurement(Storage* _Storage){

    printf("Enter temperature: ");

    char* buffer_temp = GetUserInputChar();

    char time_string[20];

    current_time(time_string, sizeof(time_string));

    storage_add_to_local_list(_Storage, time_string, buffer_temp, DEVICE_ID);

    free(buffer_temp);
    return 0;
}



char* GetUserInputChar(){
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    char *return_string = strdup(buffer);
    return return_string;
}

void current_time(char* buffer, size_t buffer_size) {
    time_t now = time(NULL);
    struct tm* t = gmtime(&now);

    strftime(buffer, buffer_size, "%Y-%m-%d %H:%M:%S", t); 
}

