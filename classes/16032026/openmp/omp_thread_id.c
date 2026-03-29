#include <stdio.h>
#include <omp.h>

int  main() {
  int total_thread = omp_get_max_threads();
  #pragma omp parallel
  {
    int thread_id = omp_get_thread_num();
    printf("Thread ID: %d/%d Say hello \n", (thread_id + 1), total_thread);
  }

  return 0;
}
