#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
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

int main()
{
  struct sockaddr_in client_addr,server_addr;
  int client_fd;
  char buffer[1024],*msg;

  if((client_fd=socket(AF_INET,SOCK_STREAM,0))==-1)
  {
   printf("Client Socket Failed...\n");
   exit(0);
  }

  memset(&server_addr,'0',sizeof(server_addr));

  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(PORT);

  if(inet_pton(AF_INET,"192.168.43.5",&server_addr.sin_addr)<=0)
  {
    printf("Address not Supported\n");
    exit(0);
  }
  
  if(connect(client_fd,(struct sockaddr *) &server_addr, sizeof(server_addr))==-1)
  {
    printf("Error while connecting\n");
    exit(0);
  }

  printf("Connected to server...\n");
  while(1)
  {
   msg=getTypedMessage();
   send(client_fd,msg,strlen(msg),0);
   int readstatus=read(client_fd,buffer,1024);
   system("mplayer /usr/share/sounds/ubuntu/ringtones/Harmonics.ogg ");
   system("clear");
   printf("\nServer says: %s\n",buffer);
   if(strcmp(buffer,"BYE")==0)
    { 
      send(client_fd,"BYE",3,0);
      exit(0);
    }
  }

  return 0;
}
