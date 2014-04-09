#include "malloc.h"

static Header *freelist = NULL;
static char buffer[BUFSIZE];

/*
 * Used when a smaller block of space can be carved out from a bigger one 
 * for allocation purposes. The remainder of unneeded space in the initial 
 * big block will be pointed to by the allocated block header. |size| 
 * represents the size of the block to be allocated by the caller. |curr| 
 * represents the Header pointer to the initial big block. The remainder 
 * block left as excess, pointed to by the allocated block header, is returned.
 */
static Header *carveHeader(int size, Header *curr) {
   char *pos = curr;
   Header *newHeader = (Header *)(pos + sizeof(Header) + size);
   newHeader->free = 1;
   newHeader->size = curr->size - size - sizeof(Header);
   newHeader->next = curr->next;
   curr->next = newHeader;
   return newHeader;
}

/*
 * Pushes |add| to the back of the freelist. |add|->next will be automatically
 * set to NULL to signify the end of the freelist
 */
static void push_back(Header *add) {
   Header *h = freelist, *prev = NULL;
   
   while (h) {
      prev = h;
      h = h->next;
   }

   add->next = NULL;
   if (prev)
      prev->next = add;
   else {
      freelist = add;
   }
}

/*
 * Merges contiguous free blocks in the freelist
 */
static void defrag() {
   Header *curr = freelist, *prev = NULL, *first = NULL;
   int sum = 0;

   while (curr) {
      if (curr->free) {
         if (!prev || !prev->free) 
            first = curr; 

         sum += curr->size;
         if (!curr->next || !curr->next->free) {
            first->size = sum;
            sum = 0;
            first->next = curr->next;
         }
      }

      prev = curr;
      curr = curr->next;
   }
}

/*
 * Traverses the freelist and prints out header information
 */
void checkFreelist() {
   Header *h = freelist;
   while (h) {
      snprintf(buffer, BUFSIZE, "at: %d, free: %d, size: %d, next: %d",
       h, h->free, h->size, h->next);
      puts(buffer);
      h = h->next;
   }
   snprintf(buffer, BUFSIZE, "current section break: %d", sbrk(0));
   puts(buffer);
   printf("\n");
}

void *myCalloc(size_t nmemb, size_t size) {
   void *block = myMalloc(nmemb * size);
   memset(block, 0, nmemb * size);
   return block;
}

void *myMalloc(size_t size) {
   Header *curr = freelist, *prev = NULL, *first = NULL;

   defrag(); 
   while (curr) {
      if (curr->free && curr->size >= size) {
         if (curr->size > size) {
            curr->next = carveHeader(size, curr);
            curr->size = size;
         }
         curr->free = 0;
         return ++curr;
      }

      curr = curr->next;
   }

   Header *header = sbrk(sizeof(Header) + size);     
   if (header < 0)
      return NULL;

   header->free = 0;
   header->size = size;
   push_back(header);

   return ++header;
}

void myFree(void *ptr) {
   Header *h = (Header *)ptr - 1;
   h->free = 1;
}

void *myRealloc(void *ptr, size_t size) {
   if (!ptr)
      return myMalloc(size);
   defrag();

   Header *curr = (Header *)ptr - 1;
   int sum = curr->size;

   curr = curr->next;
   while (curr && curr->free) {
      sum += curr->size;
      curr = curr->next;
   }

   curr = (Header *)ptr - 1;
   if (sum >= size) {
      if (sum > size) {
         Header *oldHeader = curr->next;
         Header *newHeader = (char *)curr + sizeof(Header) + size;
         newHeader->next = oldHeader->next;
         newHeader->size = sum - size;
         newHeader->free = 1;

         curr->next = newHeader;
      }
      else if (sum == size) 
         curr->next = curr->next->next;

      curr->size = size;
   }
   else {
      curr->free = 0;
      char *oldLocation = ++curr;
      char *newLocation = myMalloc(size);
      memmove(newLocation, oldLocation, curr->size);
      curr = (Header *)newLocation - 1;
   }

   return curr + 1;
}
