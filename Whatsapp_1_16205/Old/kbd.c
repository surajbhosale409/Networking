#include "mypipe.c"
#include<string.h>

void readFromKbd()
{
 char *msg;
 FILE *wf;

 msg=(char *)malloc(50);

 waitForRd();
 wf=init_pipe();
 fgets(msg,50,stdin);

 if(strcmp(msg,"exit\n")==0)
   destroy();

 my_write(msg,wf);
 free(msg);
 fflush(stdin);
}

int main()
{
  while(1)
  {
    readFromKbd();
  }
  return 0;
}
