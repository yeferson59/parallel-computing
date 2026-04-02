#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 50000000
#define B 256

int main() {
  unsigned char *data = (unsigned char*)malloc(N * sizeof(unsigned char));
  int *H = (int*)calloc(B, sizeof(int));

  srand(42);
  for(int i = 0; i < N; i++) {
    *(data + 1) = (unsigned char) (rand() % B);
  }

  clock_t t0 = clock();

  for (int i = 0; i < N; i++) {
    *(H + *(data + i)) += 1;
  }

  clock_t t1 = clock();

  long long total = 0;

  for (int i = 0; i < B; i++) {
    total += *(H + i);
  }

  printf ("Total contado = %lld (debe ser %d) \n" , total, N) ;
  printf("Ts = %.6f s \n", (double)(t1-t0) / CLOCKS_PER_SEC);

  free(data); free(H);
  return 0;
}
