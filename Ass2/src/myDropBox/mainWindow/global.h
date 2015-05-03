#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <malloc.h>
#define FAIL    -1


using namespace std;

// Global definitions of client socket
extern int sockfd;
extern int bytesReceived;
extern char recvBuff[256];
extern char message[256];
extern const char *msg;
extern struct sockaddr_in serv_addr;
extern const char* ip_addr;
extern int portNumber;
extern string msgstr;
extern string localFolderPath;
extern SSL_CTX *ctx;
extern SSL* ssl;
void ShowCerts(SSL* ssl);
SSL_CTX* InitCTX(void);

#endif // GLOBAL_H
