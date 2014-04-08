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
   char *x, *y, *z;

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

   myFree(x);
   simplePrint("freeing that 20 bytes...");
   checkFreelist();

   x = myMalloc(21); 
   simplePrint("allocating 21 bytes...");
   checkFreelist();

   myFree(x);
   simplePrint("freeing that 21 bytes...");
   checkFreelist();

   x = myMalloc(30); 
   simplePrint("allocating 30 bytes...");
   checkFreelist();

   myFree(x);
   simplePrint("freeing that 30 bytes...");
   checkFreelist();
   
   x = myMalloc(100); 
   simplePrint("allocating 100 bytes...");
   checkFreelist();

   y = myMalloc(101); 
   simplePrint("allocating 101 bytes...");
   checkFreelist();

   myFree(y);
   simplePrint("freeing that 101 bytes...");
   checkFreelist();

   y = myMalloc(102); 
   simplePrint("allocating 102 bytes...");
   checkFreelist();

   myFree(y);
   simplePrint("freeing that 102 bytes...");
   checkFreelist();

   y = myMalloc(200); 
   simplePrint("allocating 203 bytes...");
   checkFreelist();

   y = myMalloc(64000);
   simplePrint("allocating 64K bytes...");
   checkFreelist();

   myFree(y);
   simplePrint("freeing that 64K bytes...");
   checkFreelist();

   y = myMalloc(1024);
   simplePrint("allocating 1K bytes...");
   checkFreelist();

   z = myMalloc(64000);
   simplePrint("allocating 64K bytes...");
   checkFreelist();

   myFree(z);
   simplePrint("freeing that 64K bytes...");
   checkFreelist();

   z = myMalloc(100);
   simplePrint("allocating 100 bytes...");
   checkFreelist();

   myFree(x);
   myFree(y);
   myFree(z);
   checkFreelist();
   myMalloc(64000);
   checkFreelist();
#elif USING_REG_MALLOC
   int *x = malloc(16000 * sizeof(int));
#endif

   /*
   int i;
   for (i = 0; i < 64000; i++) 
      z[i] = i % 128;
   */

   return 0;
}
