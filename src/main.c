#include <stdio.h>

#include <stdlib.h>

#include "tcp_client.h"
#include "storage/storage.h"
#include "utils/montime.h"

int main(){
    
    printf("Hello world!\n\n");
    
    /* ########     DUMMY DATA START       ########### */
    LocalList LLData;

    LL_init(&LLData);

    /* ########     DUMMY DATA END       ########### */


    /* ########     TCP CLIENT START     ######### */
    printf("Start of TCP\n");
    TCPClient client;

    TCPClient_Initiate(&client);
/*if (TCPClient_Connect(&client, "142.250.74.132", "80") != 0)*/
    if (TCPClient_Connect(&client, "142.250.74.132", "80") != 0)
    {
        printf("Failed to connect to server\r\n");
        return -1;
    }else   printf("Success connecting to server using file descriptor: [%d]\n", client.fd);

    /* WRITE TO SERVER #################*/
    char* request ="GET / HTTP/1.1\r\nhost: 142.250.74.132:80\r\n\r\n";
    const char* ptr = &request[0];
    int bytesLeft = strlen(request);

    uint64_t now = SystemMonotonicMS();
    uint64_t timeout = now + 5000;
        printf("Bytes left: %i\n", bytesLeft);
    while(bytesLeft > 0 && now < timeout)
    {
        now = SystemMonotonicMS();
        
        int bytesSent = TCPClient_Write(&client, (uint8_t*)ptr, bytesLeft);
        printf("Bytes sent: %i\n", bytesSent);
        if(bytesSent > 0)
        {
            ptr += bytesSent;
            bytesLeft -= bytesSent;
            printf("Bytes sent: %i\n", bytesSent);
            printf("Bytes left: %i\n", bytesLeft);
        }
    }


    /* READ RESPONSE ###############*/
    char buffer[1024] = {0};
    int totalBytesRead = 0;

    now = SystemMonotonicMS();
    timeout = now + 5000;

    while(now < timeout){
        now = SystemMonotonicMS();
        int bytesRead = TCPClient_Read(&client, (uint8_t*)buffer, sizeof(buffer));

        if(bytesRead > 0){
            totalBytesRead += bytesRead;
        }
        else if(bytesRead == 0)
            break;
    }

    printf("Size of incomming message: %li\n", strlen(buffer));

    printf("Buffer content: %s\n", buffer);


    TCPClient_Disconnect(&client);
    TCPClient_Dispose(&client);

    /* ########     TCP CLIENT END       ######### */
    return 0;
}