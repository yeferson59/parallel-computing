#include <stdio.h>

int is_prime(int number) {
  for(int i = 2; i*i < number; i++) {
    if(number % i == 0) return 0;
  }

  return 1;
}

int main() {
  int number;
  printf("");
  scanf("");
  return 0;
}
