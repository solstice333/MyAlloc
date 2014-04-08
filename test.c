#include <stdio.h>
#include "malloc.h"
#include <stdlib.h>

#define USING_MY_MALLOC 1
#define USING_REG_MALLOC 0

#define BUFSIZE 1024

void simplePrint(char *s) {
   char buffer[BUFSIZE];
   snprintf(buffer, BUFSIZE, "%s", s);
   puts(buffer);
}

int main(int argc, char **argv) {
   char *x;

#if USING_MY_MALLOC
   x = myMalloc(4);
   simplePrint("allocating 4 bytes...");
   checkFreelist();

   myFree(x);
   simplePrint("freeing that 4 bytes...");
   checkFreelist();

   x = myMalloc(20); 
   simplePrint("allocating 20 bytes...");
   checkFreelist();
#elif USING_REG_MALLOC
   int *x = malloc(16000 * sizeof(int));
#endif

   int i;
   for (i = 0; i < 20; i++) 
      x[i] = 0 + i;

   return 0;
}
