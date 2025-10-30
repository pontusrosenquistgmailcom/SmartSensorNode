#ifndef __SSN_H__
#define __SSN_H__

#define SERVER "www.httpbin.org"
#define PORT "80"

#include <stdio.h>
#include <stdlib.h>

#include "tcp/clienttoserver.h"
#include "storage/storage.h"
#include "httpbuilder/httpbuilder.h"
#include "measure/measure.h"

#define SERVER "www.httpbin.org"
#define PORT "80"

char* build_http_payload(void* _Context);

int ssn_run_client(Storage* _Storage);


#endif