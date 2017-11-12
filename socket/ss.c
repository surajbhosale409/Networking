#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 8080

char * getTypedMessage()
{
  char *msg;
  printf("Type your msg: ");
   gets(msg);
  return msg;
}


int main(int argc,char *argv[])
{
 int socket_fd,client_fd;
 char buffer[1024],*smsg;

 int opt=1;
 struct sockaddr_in addr;

 if((socket_fd=socket(AF_INET,SOCK_STREAM,0))==-1)
 {
   printf("Socket Creation Failed...");
   exit(0);
 }

 if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))==-1)
 {
   printf("Setting socket options failed...");
   exit(0);
 }


 addr.sin_family=AF_INET;
 addr.sin_addr.s_addr=INADDR_ANY;
 addr.sin_port=htons(PORT);

 if(bind(socket_fd,(struct sockaddr *) &addr,sizeof(addr))<0)
 {
 printf("Binding failed...");
  exit(0);
 }

 if(listen(socket_fd,2)==-1)
 {
   printf("Socket not listening...");
   exit(0);
 }
 printf ("Waiting for client\n");
 int addrlen=sizeof(addr);

 client_fd=accept(socket_fd,(struct sockaddr *) &addr,(socklen_t *) &addrlen);


 while(1)
 {
    if(client_fd>-1)
  {
    int readstatus=read(client_fd,buffer,1024);
    printf("Client Says: %s\n",buffer);

    if(strcmp("BYE",buffer)==0)
      exit(0);

    printf("Type your msg: ");
    scanf("%s",smsg);
    send(client_fd,smsg,strlen(smsg),0);
  }
 }

 return 0;
}

