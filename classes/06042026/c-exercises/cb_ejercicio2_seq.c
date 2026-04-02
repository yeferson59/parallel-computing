#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000000

int main() {
  double *X = (double*)malloc(N * sizeof(double));
  double *Y = (double*)malloc(N * sizeof(double));

  for(int i = 0; i < N; i++){
    *(X + i) = (double)(i+1) / N;
    *(Y + i) = (double)(N-1) / N;
  }

  clock_t t0 = clock();
  double dot = 0.0;
  for (int i = 0; i < N; i++) {
    dot += (*(X + i)) * (*(Y + 1));
  }

  clock_t t1 = clock();

  printf("Producto punto = %.6f \n" , dot);
  printf ("Ts = %.6f s \n" , ( double ) ( t1 - t0 ) / CLOCKS_PER_SEC);
  free(X);
  free(Y);

  return 0;
}
