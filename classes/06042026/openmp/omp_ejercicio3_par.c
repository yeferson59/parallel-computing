#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define R 40000
#define C 50000

int main() {
  int total_threads = omp_get_max_threads();
  float *M = (float*)malloc((long)R * C * sizeof(float));
  float *Mp = (float*)malloc((long)R * C * sizeof(float));

  #pragma omp parallel for
  for (int i = 0; i < R; i++){
    for(int j = 0; j < C; j++) {
      *(M + (long)i*C + j) = (float)(i*C + j + 1);
    }
  }

  double tp0 = omp_get_wtime();

  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    int nthr = omp_get_num_threads();
    int chunck_size = R / total_threads;
    int start =  tid * chunck_size;
    int end = (tid + 1) < nthr ? (start + chunck_size) : R;

    for (int i = start; i < end; i++) {
      float mx = *(M + (long)i*C);

      for(int j = 1; j < C; j++) {
        if (*(M + (long)i*C + j) > mx) {
          mx = *(M + (long)i*C + j);
        }
      }

      for(int j = 0; j < C; j++) {
        *(Mp + (long)i*C + j) = *(M + (long)i*C + j) / mx;
      }
    }
  }

  double tp1 = omp_get_wtime();

  printf("M'[0][0]=%.6f M'[R-1][C-1]=%.6f\n", *Mp, *(Mp + (long)(R - 1)*C + (C - 1)));
  printf("Ts = %.6f s\n", (tp1 - tp0));

  for(int i = 0; i< 10; i++) {
    printf("%f", *(Mp + i));
  }

  free(M);
  free(Mp);

  return 0;
}
