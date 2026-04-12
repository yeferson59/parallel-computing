#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 3000
#define K 3000

int main() {
  double *A = (double*)malloc(M * K * sizeof(double));
  double *x = (double*)malloc(K * sizeof(double));
  double *y = (double*)calloc(M, sizeof(double));

  for(int i = 0;i < M; i++) {
    for(int j = 0;j < K; j++){
      *(A + i*K + j) = (double)(i + j + 1) / (M * K);
    }
  }

  for(int i = 0; i < K; i++) {
    *(x + i) = (double)(i + 1) / K;
  }

  clock_t t0 = clock();

  for (int i = 0; i < M; i++) {
    double s = 0.0;
    for(int j = 0; j < K; j++) {
      s += (*(A + (long)i*K + j)) * (*(x + j));
    }
    *(y + i) = s;
  }

  clock_t t1 = clock();

  printf ("y [0]= %.6f y [M -1]= %.6f \n" , *y, *( y +M -1));
  printf (" Ts = %.6f s \n" , (double)(t1 - t0) / CLOCKS_PER_SEC);
  free(A); free(x); free(y);

  return 0;
}
