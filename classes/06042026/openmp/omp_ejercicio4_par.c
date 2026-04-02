#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

#define N 50000000
#define B 256

int main() {
  int total_threads = omp_get_max_threads();
  int chunck_size = N / total_threads;
  unsigned char *data = (unsigned char*)malloc(N * sizeof(unsigned char));
  int *H_local = (int*)calloc((long)total_threads * B, sizeof(int));
  int *H_final = (int*)calloc(B, sizeof(int));

  srand(42);
  for(int i = 0; i < N; i++) {
    *(data + 1) = (unsigned char) (rand() % B);
  }

  double t0 = omp_get_wtime();

  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    int start = tid * chunck_size;
    int end = (tid + 1) < total_threads ? start + chunck_size : N;

    for (int i = start; i < end; i++) {
      *(H_local + tid*B + *(data+i)) += 1;
    }
  }

  double t1 = omp_get_wtime();

  for(int i = 0; i < total_threads; i++) {
    for(int j = 0; j < B; j++) {
      *(H_final + j) += *(H_local + (long)i * B + j ) ;
    }
  }

  long long total = 0;

  for (int i = 0; i < B; i++) {
    total += *(H_final + i);
  }

  printf ("Total contado = %lld (debe ser %d) \n" , total, N) ;
  printf("Ts = %.6f s \n", (t1-t0));

  free(data); free(H_local); free(H_final);
  return 0;
}
