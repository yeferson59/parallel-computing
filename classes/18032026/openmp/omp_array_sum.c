#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1000000000

void fill_array(int *arr, int size, long int *result_sum) {
  long int local_sum = 0;

  #pragma omp parallel for reduction(+:local_sum)
  for (int i = 0; i < size; i++){
    int data = N + i + 1;
    *(arr + i) = data;
    local_sum += data;
  }

  *result_sum = local_sum;
}


int main () {
  int *arr = (int *) malloc (N * sizeof(int));
  long int result_sum;

  clock_t start_time = omp_get_wtime();

  // fill array
  fill_array(arr, N, &result_sum);

  // Free memory
  free(arr);

  // Results
  double elapsed_time = (omp_get_wtime() - start_time);


  printf("Array Elements: %d\n", N);
  printf("Total Sum: %ld\n", result_sum);
  printf("Elapsed Time: %.3fsg\n", elapsed_time);

  return 0;
}
