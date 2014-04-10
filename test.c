#include <stdio.h>
#include "malloc.h"
#include <stdlib.h>
#include <assert.h>

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
   int i;

#if USING_MY_MALLOC
   x = myMalloc(5);
   simplePrint("allocating 5 bytes...");
   checkFreelist();

   for (i = 0; i < 5; i++)
      x[i] = 85;
   
   y = myMalloc(5); 
   simplePrint("allocating 5 bytes...");
   checkFreelist();

   myFree(y);
   simplePrint("freeing that 5 bytes...");
   checkFreelist();

   myFree(myMalloc(7)); 
   simplePrint("allocating and freeing 7 bytes...");
   checkFreelist();

   z = myMalloc(10); 
   simplePrint("allocating 10 bytes...");
   checkFreelist();

   myFree(z); 
   simplePrint("freeing that 10 bytes...");
   checkFreelist();

   myFree(x + 4);
   simplePrint("freeing old x...");
   checkFreelist();

   x = myRealloc(x, 50);
   simplePrint("reallcating 50 bytes...");
   checkFreelist();

   for (i = 0; i < 5; i++)
      fprintf(stderr, "%d\n", x[i]);
   fprintf(stderr, "\n");

   x = myRealloc(NULL, 20);
   simplePrint("reallocating NULL to 20 bytes...");
   checkFreelist();

   for (i = 0; i < 20; i++)
      x[i] = i + 1;
   fprintf(stderr, "\n");

   myFree(x);
   simplePrint("freeing x...");
   checkFreelist();

   x = myCalloc(20, 1);
   simplePrint("calloc 20 bytes");
   checkFreelist();

   for (i = 0; i < 20; i++)
      assert(!x[i]);
   fprintf(stderr, "\n");

   myFree(myMalloc(65000));
   simplePrint("allocating then freeing 64K...");
   checkFreelist();

   x = myCalloc(32768, 1);
   simplePrint("calloc 32768 bytes and assigning to x...");
   checkFreelist();

   for (i = 0; i < 32768; i++)
      assert(!x[i]);
   for (i = 0; i < 32768; i++) 
      x[i] = 100;

   x = myRealloc(x, 16120);
   simplePrint("realloc that 32768 down to 16120...");
   checkFreelist();

   for (i = 0; i < 16120; i++) 
      assert(x[i] == 100);

   fprintf(stderr, "\n");

#elif USING_REG_MALLOC
   int *x = malloc(16000 * sizeof(int));
#endif

   return 0;
}
