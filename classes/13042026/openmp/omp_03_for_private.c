#include <stdio.h>
#include <omp.h>

int main() {
  int arr[] = {1,2,4,5,6,7};
  int size = sizeof(arr) / sizeof(arr[0]);

  int squart = 0;

  #pragma omp parallel for private(squart)
  for(int i = 0; i < size; i++){
    squart = (*(arr + i)) * (*(arr + i));

    printf("hilo %d numero %d al cuadrado es %d \n",omp_get_thread_num(), *(arr + i), squart);
  }

  return 0;
}
