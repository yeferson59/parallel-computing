#include <stdio.h>

int main() {
  int x = 5;
  int *px = &x;


  printf("%p\n", &x);
  printf("%d\n", x);
  printf("%p\n", px);
  printf("%d\n", *px);

  *px = 10;

  printf("%p\n", &x);
  printf("%d\n", x);
  printf("%p\n", px);
  printf("%d\n", *px);

  return 0;
}
