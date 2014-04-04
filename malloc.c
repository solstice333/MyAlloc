#include <malloc.h>
#include <stdio.h>

void *calloc(size_t nmemb, size_t size) {
   fprintf(stderr, "inside your calloc\n");
   return NULL;
}

void *malloc(size_t size) {
   fprintf(stderr, "inside your malloc\n");
   return NULL;
}

void free(void *ptr) {
   fprintf(stderr, "inside your free\n");
}

void *realloc(void *ptr, size_t size) {
   fprintf(stderr, "inside your realloc\n");
}
