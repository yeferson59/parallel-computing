#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 20000000

int main() {
  int *A = (int *)malloc(N * sizeof(int));
  int *B = (int *)malloc(N * sizeof(int));
  long long *C = (long long *)malloc(N * sizeof(long long));

  for (int i = 0; i < N; i++) {
    *(A + i) = i + 1;
    *(B + i) = N - 1;
  }

  clock_t t0 = clock();

  long long total = 0;

  for (int i = 0; i < N; i++) {
    *(C + i) = (*(A + i)) + (*(B + i));
    total += *(C + i);
  }

  clock_t t1 = clock();
  double ts = (double)(t1 - t0) / CLOCKS_PER_SEC;

  printf ("Total = %lld \n", total);
  printf ("Tiempo secuencial Ts = %.6f s \n", ts);

  free(A);
  free(B);
  free(C);
  return 0;
}
