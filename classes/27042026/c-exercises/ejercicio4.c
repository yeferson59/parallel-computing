#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000000

void fill_arr(int *arr) {
  for(int i = 0; i < N; i++) {
    *(arr + i) = i + 1;
  }
}

int main() {
  int *arr = (int *)malloc(N * sizeof(int));

  fill_arr(arr);

  clock_t t0 = clock();

  long result = 0;
  for (int i = 0; i < N; i++) {
    result += *(arr + i);
  }

  clock_t t1 = clock();

  printf("%ld time elaped %.3fs\n", result, (double) (t1 - t0) / CLOCKS_PER_SEC); // 0.013s

  return 0;
}
