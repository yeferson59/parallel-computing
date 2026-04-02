#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 50000000

int isPrime(int n) {
  if (n < 2) return 0;

  for (int i = 2; i <=sqrt(n); i++) {
    if (n % i == 0) return 0;
  }

  return 1;
}

int main() {
  int total_threads = omp_get_max_threads();
  int chuck_size = N / total_threads;
  int *acc = (int*)calloc(total_threads, sizeof(int));

  double startTime = omp_get_wtime();
  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    int start = tid * chuck_size;
    int end = (tid + 1) < total_threads ? (start + chuck_size) : (N + 1);
    start = tid == 0 ? 2 : start;

    printf("start %d, end %d \n", start, end);

    for (int i = start; i < end; i++) {
      if (isPrime(i)) *(acc + tid) += 1;
    }
  }

  int counter_primes = 0;
  #pragma omp parallel for
  for(int i = 0; i < total_threads; i++) {
    counter_primes += *(acc + i);
  }

  double elapsed_time = omp_get_wtime() - startTime;

  printf("Primes found: %d\n", counter_primes);
  printf("Parallel Time: %.3fsg\n", elapsed_time);
}
