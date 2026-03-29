#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 10000000

int main() {
  int total_threads = omp_get_max_threads();
  double *X = (double*)malloc(N * sizeof(double));
  double *Y = (double*)malloc(N * sizeof(double));
  double *acc = (double *)calloc(total_threads, sizeof(double));

  for(int i = 0; i < N; i++){
    *(X + i) = (double)(i + 1) / N;
    *(Y + i) = (double)(N - 1) / N;
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
      *(acc + tid) += (*(X + i)) * (*(Y + i));
    }
  }

  double tp1 = omp_get_wtime();

  double dot = 0.0;
  for(int i = 0; i < total_threads; i++) {
    dot += *(acc + i);
  }

  printf("Producto punto = %.6f \n" , dot);
  printf ("Ts = %.6f s \n" , tp1 - tp0);
  free(X);
  free(Y);
  free(acc);
}
