#include "mypipe.c"



int main()
{
  fputs("Type enter 'exit' in kbd to terminate\n",stdout);
  while(1)
  {
    waitForWr();
    my_read();
  }
  return 0;
}
