#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define R 40000
#define C 50000

int main() {
  float *M = (float*)malloc((long)R * C * sizeof(float));
  float *Mp = (float*)malloc((long)R * C * sizeof(float));

  for (int i = 0; i < R; i++){
    for(int j = 0; j < C; j++) {
      *(M + (long)i*C + j) = (float)(i*C + j + 1);
    }
  }

  clock_t t0 = clock();

  for (int i = 0; i < R; i++) {
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

  clock_t t1 = clock();

  printf("M'[0][0]=%.6f M'[R-1][C-1]=%.6f\n", *Mp, *(Mp + (long)(R - 1)*C + (C - 1)));
  printf("Ts = %.6f s\n", (double)(t1 - t0) / CLOCKS_PER_SEC);

  for(int i = 0; i< 10; i++) {
    printf("%f", *(Mp + i));
  }

  free(M);
  free(Mp);

  return 0;
}
