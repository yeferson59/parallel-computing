#include <stdio.h>
#include <stdlib.h>

#define N 1000000

int is_perfect(int number) {
  int result = 0;

  for(int i = 1; i < number; i++) {
    if(number % i == 0) {
      result += i;
    }
  }

  return result == number ? 1 : 0;
}

void printArray(int *array, int size) {
  printf("[");
  for (int i = 0; i < (size - 1); i++) {
    printf("%d,", *(array + i));
  }
  printf("%d] \n", *(array + (size - 1)));
}

int main() {
  int *arr = (int *)malloc(N * sizeof(int));
  int size = 0;

  for (int i = 1; i < N; i++) {
    if(is_perfect(i)) {
      *(arr + size) = i;

      size++;
    }
  }


  printArray(arr, size);
  return 0;
}
