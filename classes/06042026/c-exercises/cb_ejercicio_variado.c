#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 15

int is_even(int number) {
  return number % 2 == 0 ? 1: 0;
}

void bubble_sort(int *array, int size) {
  for(int i = 0;  i < (size - 1); i++){
    for(int j = 0; j < size - i - 1; j++){
      int temp = *(array + j);

      if(temp > *(array + j + 1)) {
        *(array + j) = *(array + j + 1);

        *(array + j + 1) = temp;
      }
    }
  }
}

void reflect(int *array, int size) {
  int tem = *array;

  *array = *(array + (size - 1));
  *(array + (size - 1)) = tem;
}

void print_array(int *array, int size) {
  printf("[");
  for(int i = 0; i < size; i++) {
    int pos = *(array + i);
    if((i + 1) == size) {
      printf("%d", pos);
      break;
    };

     printf("%d,", pos);
  };

  printf("] \n");
}


int sum_array(int *array, int size) {
  int result = 0;
  for (int i = 0; i < size; i++) {
    result += *(array + i);
  }

  return result;
}

int high(int *array, int size) {
  int result = *array;

  for (int i = 1; i < size; i++) {
    int number = *(array + i);
    if(result < number) result = number;
  }

  return result;
}

int low(int *array, int size) {
  int result = *array;

  for (int i = 1; i < size; i++) {
    int number = *(array + i);
    if(result > number) result = number;
  }

  return result;
}


int main() {
  int odd_num = 0;
  int even_num = 0;

  int *odd_numbers = (int*)malloc(N * sizeof(int));
  int *even_numbers = (int*)malloc(N * sizeof(int));

  srand(time(NULL));
  for(int i = 0; i < N; i++) {
    int number = (rand() % 9) + 1;

    if(is_even(number)) {
      *(even_numbers + even_num) = number;

      even_num++;
    } else {
      *(odd_numbers + odd_num) = number;

      odd_num++;
    }
  }

  bubble_sort(odd_numbers, odd_num);
  bubble_sort(even_numbers, even_num);

  reflect(odd_numbers, odd_num);
  reflect(even_numbers, even_num);

  int *head_even_odd_arr = (int*)malloc(odd_num * sizeof(int));
  int *tail_even_odd_arr = (int*)malloc(odd_num * sizeof(int));
  int *head_odd_even_arr = (int*)malloc(even_num * sizeof(int));
  int *tail_odd_even_arr = (int*)malloc(even_num * sizeof(int));

  for(int i = 0; i < odd_num; i++) {
    *(head_even_odd_arr + i) = (*even_numbers) * (*(odd_numbers + i));
  }

  for(int i = 0; i < odd_num; i++) {
    *(tail_even_odd_arr + i) = *(even_numbers + (even_num - 1)) * (*(odd_numbers + i));
  }

  for(int i = 0; i < even_num; i++) {
    *(head_odd_even_arr + i) = *(odd_numbers) * (*(even_numbers + i));
  }

  for(int i = 0; i < even_num; i++) {
    *(tail_odd_even_arr + i) = *(odd_numbers + (odd_num - 1)) * (*(even_numbers + i));
  }

  int *sum_arrays = (int*)calloc(4, sizeof(int));

  *(sum_arrays) = sum_array(head_even_odd_arr, odd_num);
  *(sum_arrays + 1) = sum_array(tail_even_odd_arr, odd_num);
  *(sum_arrays + 2) = sum_array(head_odd_even_arr, even_num);
  *(sum_arrays + 3) = sum_array(tail_odd_even_arr, even_num);


  print_array(sum_arrays, 4);

  printf("max = %d, min = %d \n", high(sum_arrays, 4), low(sum_arrays, 4));

  free(odd_numbers);
  free(even_numbers);
  free(head_even_odd_arr);
  free(tail_even_odd_arr);
  free(head_odd_even_arr);
  free(tail_odd_even_arr);
  free(sum_arrays);

  return 0;
}
