#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "httpparser.h"

#include "../utils/strdup.h"

/*
EXAMPLE OF HTTP TEXT:

GET /weather?city=Stockholm HTTP/1.1\r\n
Host: 127.0.0.1\r\n
User-Agent: curl/8.0\r\n
Content-Length: 9\r\n\r\n
BODY TEXT\r\n

TO HELP MAKE PARSER LOGIC.
*/


/* Private functions */

int http_parseRequestLine(char* _Line, HttpRequestBlob* _HttpBlob);

int http_parseHeaderLines(char* _Line, HttpRequestBlob* _HttpBlob);

int http_parse(const char* _InBuffer)
{
    HttpRequestBlob* httpData = (HttpRequestBlob*)malloc(sizeof(HttpRequestBlob));
    memset(httpData, 0, sizeof(HttpRequestBlob));

    char* dataCopy = strdup(_InBuffer);

    char* pch;

    pch = strtok(dataCopy, "\r\n");
    if(pch == NULL){
        return 1;
    }
    while (pch != NULL)
    {
        if(httpData->method != NULL && httpData->path != NULL && httpData->version != NULL){
            /* Identify headers and parse KEY and VALUE */
            http_parseHeaderLines(pch, httpData);
        }

        if(httpData->method == NULL){
            http_parseRequestLine(pch, httpData);

            free(dataCopy);
            dataCopy = strdup(_InBuffer);

            pch = strtok(dataCopy, "\r\n");
        }

        pch = strtok(NULL, "\r\n");


    }

    printf("\nAFTER LOOP\n");

    char* bodyStart = strstr(_InBuffer, "\r\n\r\n");
    if(bodyStart != NULL)
    {
        bodyStart += 4; /* move past delimiter */
        httpData->body = strdup(bodyStart);
    }    



    printf("httpdata method  : %s\n", httpData->method);
    printf("httpdata path    : %s\n", httpData->path);
    printf("httpdata version : %s\n", httpData->version);

    struct Header* hdr;
    for(hdr = httpData->Headers; hdr != NULL; hdr = hdr->next)
    {
        printf("Header Key Name  : %s\n", hdr->keyName);
        printf("header Key Value : %s\n", hdr->KeyValue);
    }

    printf("Http body        : %s", httpData->body);

    free(dataCopy);
    http_destroyBlob(httpData);

    return 0;
}

int http_parseBody();

/* Uses strtok() and will destroy input data (and any ongoing usage of strtok)*/
int http_parseRequestLine(char* _Line, HttpRequestBlob* _HttpBlob){


    char* partOfLine = strtok(_Line, " ");
    _HttpBlob->method = strdup(partOfLine);

    partOfLine = strtok(NULL, " ");
    _HttpBlob->path = strdup(partOfLine);

    partOfLine = strtok(NULL, " ");
    _HttpBlob->version = strdup(partOfLine);

    return 0;
}

/* this function should receive a charstr containing a "key: value" */
int http_parseHeaderLines(char* _Line, HttpRequestBlob* _HttpBlob){

    char* keyPart = strchr(_Line, ':');
    
    if(keyPart) {
        *keyPart = '\0';
        char* keyName = _Line;
        char* valueName = keyPart +1;
        
        while(*valueName == ' ')
        valueName++;
        
        Header* newHeader = (Header*)malloc(sizeof(Header));
        memset(newHeader, 0, sizeof(Header));

        newHeader->keyName = strdup(keyName);
        newHeader->KeyValue = strdup(valueName);
        newHeader->next = NULL;

        if(_HttpBlob->Headers == NULL)
        {
            _HttpBlob->Headers = newHeader;
        }else{
            Header* lastHdr = _HttpBlob->Headers;
            while(lastHdr->next)
                lastHdr = lastHdr->next;
            lastHdr->next = newHeader;
        }
        
        return 0;
    }
    return -1;
}

char* http_buildHttpTextBlob(char* _Method, char* _Path, char* _Version, char* _Body){

    char* httpStrBlob = (char*)malloc(4000);
    size_t contentLength = strlen(_Body);
    sprintf(httpStrBlob, "%s %s %s\r\nContent-Length: %li\r\n", _Method, _Path, _Version, contentLength);


    return 0;
}


int http_destroyBlob(HttpRequestBlob* _Blob){

    if(_Blob == NULL)
        return 0;

    free(_Blob->method);
    free(_Blob->path);
    free(_Blob->version);
    free(_Blob->body);

    Header* lastHdr = _Blob->Headers;
    while(lastHdr != NULL){

        Header* next = lastHdr->next;
        free(lastHdr->keyName);
        free(lastHdr->KeyValue);
        free(lastHdr);
        lastHdr = next;
    }
    free(_Blob);


    return 0;
}


