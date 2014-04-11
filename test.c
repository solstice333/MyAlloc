#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// set these to 0 to get it to work for both stdlib.h and custom
#define CHECK_FREELIST 1
#define FREE_X_PLUS_4 0

// executes the first test that is seen as true
#define TEST1 0
#define TEST2 0
#define TEST3 0
#define TEST4 0
#define TEST5 0
#define TEST6 1

#define BUFSIZE 1024

void simplePrint(char *s) {
   char buffer[BUFSIZE];
   snprintf(buffer, BUFSIZE, "%s\n", s);
   fputs(buffer, stderr);
}

int main(int argc, char **argv) {
   char buffer[BUFSIZE];
   char *x, *y, *z;
   int i;

#if TEST1
   x = malloc(5);
   simplePrint("allocating 5 bytes...");

#if CHECK_FREELIST
   checkFreelist();
#endif

   for (i = 0; i < 5; i++)
      x[i] = 85;
   
   y = malloc(5); 
   simplePrint("allocating 5 bytes...");

#if CHECK_FREELIST
   checkFreelist();
#endif

   free(y);
   simplePrint("freeing that 5 bytes...");

#if CHECK_FREELIST
   checkFreelist();
#endif

   free(malloc(7)); 
   simplePrint("allocating and freeing 7 bytes...");

#if CHECK_FREELIST
   checkFreelist();
#endif

   z = malloc(10); 
   simplePrint("allocating 10 bytes...");

#if CHECK_FREELIST
   checkFreelist();
#endif

   free(z); 
   simplePrint("freeing that 10 bytes...");

#if CHECK_FREELIST
   checkFreelist();
#endif
   
   x = realloc(x, 50);
   simplePrint("reallcating 50 bytes...");

#if CHECK_FREELIST
   checkFreelist();
#endif

   for (i = 0; i < 5; i++)
      assert(x[i] == 85);

#if FREE_X_PLUS_4
   free(x + 4);
#else
   free(x);
#endif

   simplePrint("freeing realloc x...");

#if CHECK_FREELIST
   checkFreelist();
#endif

   x = realloc(NULL, 20);
   simplePrint("reallocating NULL to 20 bytes...");

#if CHECK_FREELIST
   checkFreelist();
#endif

   for (i = 0; i < 20; i++)
      x[i] = i + 1;

   free(x);
   simplePrint("freeing x...");

#if CHECK_FREELIST
   checkFreelist();
#endif

   x = calloc(20, 1);
   simplePrint("calloc 20 bytes");

#if CHECK_FREELIST
   checkFreelist();
#endif

   for (i = 0; i < 20; i++)
      assert(!x[i]);

   free(malloc(65000));
   simplePrint("allocating then freeing 64K...");

#if CHECK_FREELIST
   checkFreelist();
#endif

   x = calloc(32768, 1);
   simplePrint("calloc 32768 bytes and assigning to x...");

#if CHECK_FREELIST
   checkFreelist();
#endif

   for (i = 0; i < 32768; i++)
      assert(!x[i]);
   for (i = 0; i < 32768; i++) 
      x[i] = 100;

   x = realloc(x, 16120);
   simplePrint("realloc that 32768 down to 16120...");

#if CHECK_FREELIST
   checkFreelist();
#endif

   for (i = 0; i < 16120; i++) 
      assert(x[i] == 100);

#elif TEST2
   x = malloc(10);
   checkFreelist();
   x = realloc(x, 30);
   checkFreelist();

#elif TEST3
   x = malloc(10);
   checkFreelist();
   x = realloc(x, 2);
   checkFreelist();

#elif TEST4
   for (i = 0; i < 128; i++)
      x = realloc(NULL, 65535);
   checkFreelist();
#elif TEST5
   for (i = 0; i < 32; i++) {
      if (i < 15) {
         if (i % 2) 
            x = realloc(x, 32768);
         else 
            x = malloc(65536);
      }
      else {
         if (i % 2) 
            x = realloc(x, 45);
         else
            x = malloc(32);
      }
   }
   checkFreelist();
#elif TEST6
   for (i = 0; i < 100; i++) {
      x = malloc(0);
      x = realloc(x, 0);
   }

   checkFreelist();

#endif

   return 0;
}
