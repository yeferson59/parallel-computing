#include <stdio.h>
#include <stdlib.h>

#define N 6

int *createArray(int size) {
  int *arr = (int *)calloc(size, sizeof(int));
  return arr;
}

void printArray(int *arr) {
  printf("[");
  for (int i = 0; i < (N - 1); i++) {
    printf("%d,", *(arr + i));
  }
  printf("%d]\n", *(arr + (N - 1)));
}

void initialArray(int *arr) {
  for (int i = 0; i < N; i++) {
    *(arr + i) = (2 * (i + 1)) + (i + 1);
  }
}

short is_even(int number) {
  return number % 2 == 0 ? 1 : 0;
}

void mutateArray(int *arrOriginal, int *arrResult) {
  for (int i = 0; i < N; i++) {
    if (is_even(*(arrOriginal + i))) {
      *(arrResult + i) = (2 * (*(arrOriginal + i))) + 3;
    } else {
     *(arrResult + i) = (3 * (*(arrOriginal + i))) - 2;
    }
  }
}

int calculateScalerProduct(int *arr1, int *arr2) {
  int result = 0;

  for (int i = 0; i < N; i++) {
    result += *(arr1 + i) * (*(arr2 + i));
  }

  return result;
}

int main() {
  int *arr = createArray(N);

  initialArray(arr);

  int *arr2 = createArray(N);

  mutateArray(arr, arr2);

  int *arr3 = createArray(N);

  mutateArray(arr2, arr3);

  int *arr4 = createArray(N);

  mutateArray(arr3, arr4);

  int scalarProductAB = calculateScalerProduct(arr, arr2);
  int scalarProductCD = calculateScalerProduct(arr3, arr4);

  printf ("Array A: ") ; printArray(arr) ;
  printf ("Array B: ") ; printArray(arr2) ;
  printf ("Array C: ") ; printArray(arr3) ;
  printf ("Array D: ") ; printArray(arr4) ;
  printf ("Scalar Product AB: %d \n", scalarProductAB) ;
  printf ("Scalar Product CD: %d \n", scalarProductCD) ;
  printf ("Scalar S : % d \n" , (scalarProductAB + scalarProductCD)) ;

  free (arr) ;
  free (arr2) ;
  free (arr3) ;
  free (arr4) ;
}
