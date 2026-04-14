#include <stdio.h>
#include <omp.h>

int main() {
  int nthd = omp_get_num_threads();
  #pragma omp parallel num_threads(4)
  {
    int tid = omp_get_thread_num();
    printf("hola %d de %d \n", tid, nthd);
  }
}
