#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 20000000

int main() {
  int total_threads = omp_get_max_threads();
  int *A = (int *)malloc(N * sizeof(int));
  int *B = (int *)malloc(N * sizeof(int));
  long long *C = (long long *)malloc(N * sizeof(long long));
  long long *ps = (long long *)malloc(total_threads * sizeof(long long));

  #pragma omp parallel for
  for (int i = 0; i < N; i++) {
    *(A + i) = i + 1;
    *(B + i) = N - 1;

    if(i < total_threads) {
      *(ps + i) = 0;
    }
  }

  double tp0 = omp_get_wtime();

  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    int nthr = omp_get_num_threads();
    int chunck_size = N / total_threads;
    int start =  tid * chunck_size;
    int end = (tid + 1) < nthr ? (start + chunck_size) : N;

    for(int i = start; i < end; i++) {
      *(C + i) = *(A + i) + *(B + i);
      *(ps + tid) += *(C + i);
    }
  }

  double tp1 = omp_get_wtime();

  long long total = 0;
  for ( int i = 0; i < total_threads; i++) {
    total += *(ps+i) ;
  }

  printf("Total = %lld \n", total);
  printf("Tiempo paralelo Tp = %.6f s \n", tp1 - tp0) ;

  free(A);
  free(B);
  free(C);
  return 0;
}
