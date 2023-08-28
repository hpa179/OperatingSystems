#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "myheader.h"
#include "myheaderOG.h"

int main() {

long startHeap = (unsigned long)sbrk(0);
printf("Heap start address: %p\n\n", sbrk(0));

    // Allocate and free memory blocks using malloc, calloc, realloc, and free functions
  void *p1 = malloc(10);
  printf("The malloc for p1: %p\n", p1);
   free(p1);
   printf("Memory freed, 10 bytes: %p\n\n", p1);

  void *p2 = malloc(10);
   printf("The malloc for p2: %p\n", p2);
   free(p2);
   printf("Memory freed, 10 bytes: %p\n\n", p2);
 
  void *p3 = calloc(1, 20);
   printf("The calloc for p3: %p\n", p3);
   p3 = realloc(p3, 15);
   printf("The realloc for p3: %p\n", p3);
   free(p3);
    printf("Memory freed, 20 bytes: %p\n", p3);
    printf("Memory freed, realloc 20 bytes: %p\n\n", p3);

  void *p4 = malloc(15);
   printf("The malloc for p4: %p\n", p4);
   free(p4);
   printf("Memory freed, 15 bytes: %p\n\n", p4);

  void *p5 = malloc(12);
   printf("The malloc for p5: %p\n", p5);
   free(p5);
   printf("Memory freed, 12 bytes: %p\n\n", p5);

  void *p6 = malloc(20);
   printf("The malloc for p6: %p\n", p6);
   p6 = realloc(p6, 20);
   printf("The realloc for p6(same as malloc p6): %p\n", p6);
   free(p6);
   printf("Memory freed, 20 bytes: %p\n", p6);
   printf("Memory freed, realloc 20 bytes: %p\n\n", p6);

  void *p7 = malloc(30);
   printf("The malloc for p7: %p\n", p7);
   //free(p6);
   //printf("Memory freed, 30 bytes\n");
  void *p8 = malloc(25);
   printf("The malloc for p8: %p\n", p8);
   free(p8);
   printf("Memory freed, 25 bytes: %p\n", p8);
   free(p7);
   printf("Memory freed, 30 bytes: %p\n\n", p7);

  void *p9 = calloc(2, 15);
   printf("The calloc for p9: %p\n", p9);
   free(p9);
   printf("Memory freed, 15 bytes: %p\n\n", p9);

  void *p10 = malloc(25);
   printf("The best fit for malloc for p10(25 bytes) expected to be same as p8: %p\n", p10);
   p10 = realloc(p10, 20);
   printf("p10 after realloc should be 20 bytes(same as p10): %p\n", p10);
   p10 = realloc(p10, 15);
   printf("p10 after realloc should be 15 bytes(same as p10): %p\n", p10);
   free(p10);
   printf("Memory freed, 15 bytes: %p\n\n", p10);
  
  void *p11 = calloc(3, 10);
   printf("The calloc for p11: %p\n", p11);

   void *p12 = calloc(4, 15);
   printf("The calloc for p12: %p\n", p12);
   free(p12);
   printf("Memory freed, 10 bytes: %p\n\n", p12);

  p11 = realloc(p11, 20);
   printf("Realloc should be 20 bytes(same as p11): %p\n", p11);
  free(p11);
   printf("Memory freed, 10 bytes: %p\n\n", p11);

  void *p13 = calloc(5, 20);
   printf("The calloc for p13: %p\n", p13);
  void *p14 = calloc(6, 25);
   printf("The calloc for p14: %p\n", p14);
   free(p14);
   free(p13);
    printf("Memory freed, 25 bytes: %p\n",p14);
    printf("Memory freed, 20 bytes: %p\n\n", p13);

  void *p15 = calloc(7, 25);
  p15 = realloc(p15, 25);
  void *p16 = calloc(8, 30);
   printf("The calloc for p15: %p\n", p15);
   printf("The realloc for p15(should be same as p15 calloc): %p\n", p15);
   printf("The malloc for p16: %p\n", p16);
   p16 = realloc(p16, 30);
  printf("The realloc for p16(30 bytes) same as p16 as malloc: %p\n", p16);
   free(p16);
   free(p15);
    printf("Memory freed for p16, 30 bytes: %p\n", p16);
    printf("Memory freed for p15, 25 bytes: %p\n\n", p15);

  void *p17 = malloc(30);
  printf("The malloc for p17: %p\n", p17);
  void *p18 = malloc(30);
  printf("The malloc for p18: %p\n", p18);
  p18 = realloc(p18, 30);
  printf("The realloc for p18(30 bytes) same as p18 malloc: %p\n", p18);
  free(p17);
  printf("Memory freed for p17, 30 bytes: %p\n", p17);
  free(p18);
  printf("Memory freed for p18, 30 bytes: %p\n\n", p18);

  void *p19 = calloc(9, 35);
  printf("The calloc for p19: %p\n", p19);
  void *p20 = calloc(10, 40);
  printf("The calloc for p20: %p\n", p20);
  p20 = realloc(p20, 40);
  printf("The realloc for p20: %p\n", p20);
  free(p20);
  free(p19);
  printf("Memory freed for p20, 40 bytes: %p\n", p20);
  printf("Memory freed for p19, 35 bytes: %p\n\n", p19);
  
  void *p21 = calloc(11, 42);
  printf("The calloc for p21, 42 bytes: %p\n", p21);
  void *p22 = calloc(12, 42);
  printf("The calloc for p22, 42 bytes: %p\n", p22);
  p22 = realloc(p22, 42);
  printf("The realloc for p22(42 bytes): %p\n", p22);
  p21 = realloc(p21, 40);
  printf("The realloc for p21(40 bytes): %p\n",p21);
  free(p21);
  printf("Memory freed for p21, 40 bytes: %p\n", p21);
  free(p22);
  printf("Memory freed for p22, 42 bytes: %p\n\n", p22);


  // Allocate and free memory for the first fit
  void *p23 = malloc(10);
  printf("The first fit malloc for p23: %p\n", p23);
   free(p23);
   printf("Memory freed, 10 bytes: %p\n\n", p23);

  void *p24 = malloc(10);
   printf("The first fit malloc for p24: %p\n", p24);
   free(p24);
   printf("Memory freed, 10 bytes: %p\n\n", p24);

  void *p25 = malloc(15);
   printf("The first fit malloc for p25: %p\n", p25);
   free(p25);
   printf("Memory freed, 15 bytes: %p\n\n", p25);

  void *p26 = malloc(12);
   printf("The first fit malloc for p26: %p\n", p26);
   free(p26);
   printf("Memory freed, 12 bytes: %p\n\n", p26);

   //instance for best fit is better
   /*void *p1 = malloc(100);
  printf("The malloc for p1: %p\n", p1);
  void *p3 = malloc(500);
  printf("The malloc for p3: %p\n", p3);
  void *p5 = malloc(200);
  printf("The malloc for p5: %p\n", p5);
  void *p7 = malloc(300);
  printf("The malloc for p7: %p\n", p7);

  free(p1);
   printf("Memory freed, 100 bytes: %p\n\n", p1);
   free(p3);
   printf("Memory freed, 500 bytes: %p\n\n", p3);
   free(p5);
   printf("Memory freed, 200 bytes: %p\n\n", p5);
  free(p7);
  printf("Memory freed, 300 bytes: %p\n\n", p7);
  
  void *p2 = malloc(212);
   printf("The  malloc for p2: %p\n", p2);
  void *p4 = malloc(417);
   printf("The malloc for p2: %p\n", p4);
  void *p6 = malloc(112);
   printf("The  malloc for p6: %p\n", p6);
void *p8 = malloc(426);
  printf("The malloc for p8: %p\n", p8);*/

   

     // count memory usage
    size_t memory_usage = count_memory_usage();
    printf("Total amout of memory used: %zu bytes\n", memory_usage);
    
  int *heapEnd = sbrk(0);
  printf("Heap end address: %p\n\n", heapEnd);

  printf("Memory leaks: %lu bytes\n", memoryLeaks(startHeap));
  return 0;
}