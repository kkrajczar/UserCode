#include <stdio.h>

int main()
{
  FILE *in;
  char c;

  //input file  
  in = fopen("particles.txt", "r");

  if(in != NULL) {
    while((c = fgetc(in)) != EOF) putchar(c);
    fclose(in);
  }
  else printf("Unable to open file");
  
  return 0;
}
