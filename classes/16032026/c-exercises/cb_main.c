#include <stdio.h>

int main() {
  int arr[] = {1,2,4,5,6};
  int size_arr  = sizeof(arr) / sizeof(arr[0]);

  for(int i = 0; i < size_arr; i++) {
    printf("%d\n",*(arr + i));
  }

  return 0;
}
