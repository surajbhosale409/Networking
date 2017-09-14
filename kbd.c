#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


void wait()
{
  FILE *fp;

  while(1)
  {

   fp=fopen("pipe","r");
   if(fp!=NULL)
   {
    if(fgetc(fp)==EOF)
      return ;                                //for waiting until earlier content is been read
    fclose(fp);
   }
  }
}

void kbd()
{
  FILE *fp=NULL;
  char buff[1024];

  while(1)
  {

    fp=fopen("pipe","w");

    if(fp==NULL)
     {
      fprintf(stdout,"Unable to initiate kbd\n");
      exit(1);
     }

    fgets(buff,1024,stdin);

    fputs(buff,fp);
    fclose(fp);
   

    if(strcmp(buff,"bye\n")==0)
      return ;

    wait();

  }

}

int main()
{
  kbd();
  unlink("pipe");
  return 0;
}
