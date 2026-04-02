#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 10000000

int main() {
  int total_threads = omp_get_max_threads();
  long *A = (long *)calloc(SIZE, sizeof(long));

  double tp0 = omp_get_wtime();

  #pragma omp parallel for
  for(int i = 0; i < SIZE; i ++) {
    *(A + i) = i;
  }

  double tp1 = omp_get_wtime();

  printf("%.6f \n", (tp1 - tp0));
  printf("%ld", *(A + (SIZE - 1)));

  return 0;
}
