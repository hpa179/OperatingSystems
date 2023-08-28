#ifndef myheader
#define myheader

#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "myheader.h"

void *nofree_malloc(size_t size);
void *malloc(size_t size);
void *calloc(size_t nelem, size_t elsize);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
size_t count_memory_usage();
struct block_meta *find_free_block(struct block_meta **last, size_t size);
struct block_meta *request_space(struct block_meta* last, size_t size);
struct block_meta *get_block_ptr(void *ptr);
struct block_meta *find_free(struct block_meta **last, size_t size);
long memoryLeaks(long startHeap);


#endif 