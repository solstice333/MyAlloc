#ifndef MALLOC_H
#define MALLOC_H

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

#define DEBUG_MALLOC 1
#define BUFSIZE 1024

typedef struct Header {
   int free, size;
   struct Header *next;
} Header;

void checkFreelist();
void *myCalloc(size_t nmemb, size_t size);
void *myMalloc(size_t size);
void myFree(void *ptr);
void *myRealloc(void *ptr, size_t size);

#endif
