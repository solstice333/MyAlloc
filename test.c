#include <stdio.h>
#include <malloc.h>

int main(int argc, char **argv) {
   fprintf(stderr, "assigning block to x\n");
   char *x = malloc(10);
   fprintf(stderr, "freeing x\n");
   free(x);
   return 0;
}
