#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


void wait()
{
   FILE *fp;
   while(!(fp=fopen("pipe","r")))
   {
   }                                //For waiting if file does not exists
   
   while(fgetc(fp)==EOF)
   {
     fclose(fp);                    //For waiting if file does not have any content to read
     fp=fopen("pipe","r");
   }
}




void display()
{
  FILE *fp;
  char buff[1024];

  while(1)
  {
    wait();
    fp=fopen("pipe","r"); 

    fgets(buff,1024,fp);     //Reading from file 
    fputs(buff,stdout);      //Writing to stdout
    fclose(fp);
    
    if(strcmp(buff,"bye\n")==0)
      return ;

    fp=fopen("pipe","w");    // For flushing the contents of file
    fclose(fp);
  }

}

int main()
{
  fprintf(stdout,"Type enter 'bye' in kbd  to terminate\n"); 
  display();
  return 0;
}

