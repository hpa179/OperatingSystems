#ifndef myheaderOG
#define myheaderOG

#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


void *nofree_malloc(size_t size);
void *malloc(size_t size);
void *calloc(size_t nelem, size_t elsize);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
struct block_meta *find_free_block(struct block_meta **last, size_t size);
struct block_meta *request_space(struct block_meta* last, size_t size);
struct block_meta *get_block_ptr(void *ptr);
long memoryLeaks(long startHeap);


#endif