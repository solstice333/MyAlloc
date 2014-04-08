#include "malloc.h"

static Header *freelist = NULL;

static char buffer[BUFSIZE];

/*
 * Used when a smaller block of space (let's call this block1) can be carved 
 * out from a bigger one for allocation purposes. block1 then points to 
 * the remaining excess (let's call this block2). block2 is returned by
 * carveHeader(). |size| represents the size of block2, |curr| represents
 * the pointer to the start of the initial big block, |next| represents
 * the Header pointer of the initial big block which will be redirected as 
 * block1 pointing to block2.
 */
static Header *carveHeader(int size, Header *curr, Header *next) {
   Header *newHeader = (Header *)((char *)curr + sizeof(Header) + 
    curr->size - size);
   newHeader->free = 1;
   newHeader->size = size;
   newHeader->next = next;
   return newHeader;
}

/*
 *  Pushes |add| to the back of the freelist
 */
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
}

// TODO implement this function first
void *myMalloc(size_t size) {
   Header *curr = freelist, *prev = NULL, *first = NULL;

   defrag(); 
   while (curr) {
      if (curr->free && curr->size >= size) {
         if (curr->size > size) {
            curr->next = carveHeader(curr->size - size, curr, curr->next);
            curr->size = size;
         }
         curr->free = 0;
         return ++curr;
      }

      curr = curr->next;
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
