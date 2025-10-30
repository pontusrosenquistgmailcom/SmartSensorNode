#ifndef __CLIENTTOSERVER_H__
#define __CLIENTTOSERVER_H__

typedef char* (*dataCallback)(void* _Context);

int clienttoserver_send_and_receive(char* _IPAddress, char* _Port, dataCallback callback, void* _Context);


#endif