#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void destroy()
{
  unlink("pipe");
  unlink("pipe.lock");
  exit(0);
}

int checkConn()
{
  if(access("pipe",F_OK)!=0)
    return 0;
  else
    return 1;
}



void waitForRd()
{
  while(access("pipe",F_OK)==0)
  {}
}

void waitForWr()
{
  while(access("pipe.lock",F_OK)==0)
  {
   if(!checkConn())
      exit(0);
  }
}

FILE * init_pipe()
{
  FILE *fp;
  fp=fopen("pipe","w");
  creat("pipe.lock",O_CREAT);
  return fp;
}

void my_write(char *msg,FILE *fp)
{
 fputs(msg,fp);
 fclose(fp);
 unlink("pipe.lock");
 sleep(0.1);
}


char * my_read()
{
  FILE *fp;
  char *buff;
  fp=fopen("pipe","r");
  while(!feof(fp))
  {
    putchar(fgetc(fp));
  }
 unlink("pipe");
 sleep(0.2);
}
