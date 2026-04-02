#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000000

int main() {
  long *A = (long *)calloc(SIZE, sizeof(long));

  clock_t t0 = clock();

  for(int i = 0; i < SIZE; i++) {
    *(A + i) = i;
  }

  clock_t t1 = clock();

  printf("%.6f \n", (double)(t1 - t0) / CLOCKS_PER_SEC);
}
