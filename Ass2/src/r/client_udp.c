/* UDP client in the internet domain */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void error(const char *);
int main(int argc, char *argv[])
{
   int sock, n;
   unsigned int length;
   struct sockaddr_in server, from;
	   struct sockaddr_in mine;

  sock= socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) error("socket");


   length = sizeof(mine);
   bzero(&mine,length);
   mine.sin_family=AF_INET;
   mine.sin_addr.s_addr=INADDR_ANY;
   mine.sin_port=htons(atoi(argv[3]));
   if (bind(sock,(struct sockaddr *)&mine,length)<0) 
       error("binding");

   struct hostent *hp;
   char buffer[256];
   
   if (argc != 4) { printf("Usage: server port\n");
                    exit(1);
   }
 
   server.sin_family = AF_INET;
   hp = gethostbyname(argv[1]);
   if (hp==0) error("Unknown host");

   bcopy((char *)hp->h_addr, 
        (char *)&server.sin_addr,
         hp->h_length);
   server.sin_port = htons(atoi(argv[2]));
   length=sizeof(struct sockaddr_in);

	while(1)
	{
		printf("Please enter the message: ");
		bzero(buffer,256);
		fgets(buffer,255,stdin);
		n=sendto(sock,buffer,strlen(buffer),0,(const struct sockaddr *)&server,length);
		if (n < 0) error("Sendto");
		n = recvfrom(sock,buffer,256,0,(struct sockaddr *)&from, &length);
		if (n < 0) error("recvfrom");
		write(1,"Got an ack: ",12);
		write(1,buffer,n);
	}
   close(sock);

   return 0;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}