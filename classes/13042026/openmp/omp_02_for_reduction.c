#include <stdio.h>
#include <omp.h>

int main() {
  int arr[] = {1,2,4,5,6,7};
  int size = sizeof(arr) / sizeof(arr[0]);

  int sum = 0;

  #pragma omp parallel for reduction(+:sum)
  for(int i = 0; i < size; i++){
    sum += *(arr + i);
  }

  printf("suma es %d \n", sum);

  return 0;
}
