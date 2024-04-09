#ifndef FCGI_H
#define FCGI_H

#include "fastcgi.h"

typedef struct {
    int sockfd;
    int requestId;
} Fcgi_t;

void FCGI_init(Fcgi_t *c);

void FCGI_close(Fcgi_t *c);

void setRequestId(Fcgi_t *c, int requestId);

static FCGI_Header MakeHeader(int type, int requestId, int contentLength, int paddingLength);

static FCGI_BeginRequestBody MakeBeginRequestBody( int role, int keepConnection);

static void FCGIUtil_BuildNameValueHeader(char *name, int nameLen, char *value, int valueLen, unsigned char *headerBuffPtr, int *headerLenPtr);

void sockConnect(Fcgi_t *c, char *host, int port);

int sendBeginRequestRecord(Fcgi_t *c);

int sendParams(Fcgi_t *c, char *name, char *value);

int sendEndRequestRecord(Fcgi_t *c);

void renderContent(Fcgi_t *c, char **content);

void sendBody(Fcgi_t *c, char *body);

#endif
