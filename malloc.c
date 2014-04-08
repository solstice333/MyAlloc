#include "malloc.h"

static Header *freelist = NULL;

static char buffer[BUFSIZE];

// Convenience function for creating a new header
static Header *createNewHeader(int size, Header *curr, Header *next) {
   Header *newHeader = curr + sizeof(Header) + size;
   newHeader->free = 1;
   newHeader->size = size;
   newHeader->next = next;
   return newHeader;
}

static void push_back(Header *add) {
   Header *h = freelist, *prev = NULL;
   
   while (h) {
      prev = h;
      h = h->next;
   }

   if (prev)
      prev->next = add;
   else {
      add->next = NULL;
      freelist = add;
   }
}

void checkFreelist() {
   Header *h = freelist;
   while (h) {
      snprintf(buffer, BUFSIZE, "free: %d, size: %d, next: %d",
       h->free, h->size, h->next);
      puts(buffer);
      h = h->next;
   }
}

// TODO implement this function first
void *myMalloc(size_t size) {
   Header *h = freelist;

   int sum = 0;
   while (h) {
      if (h->size > size) {
         h->next = createNewHeader(h->size - size, h, 
          h->next);

         h->free = 0;
         h->size = size;

         return ++h;
      }
      else if (h->size < size)
         sum += h->size;

      if (h->free == 0)
         sum = 0;

      h = h->next;
   }

#if DEBUG_MALLOC
   snprintf(buffer, BUFSIZE, "%s", "inside your malloc");
   puts(buffer);
#endif

   Header *header = sbrk(sizeof(Header) + size);     
   header->free = 0;
   header->size = size;
   push_back(header);

   return ++header;
}

void myFree(void *ptr) {
#if DEBUG_MALLOC
   snprintf(buffer, BUFSIZE, "%s", "inside your free");
   puts(buffer);
#endif

   Header *h = (Header *)ptr - 1;
   h->free = 1;
}
