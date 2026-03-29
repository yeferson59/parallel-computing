#include <stdio.h>

int contains(int *arr, int size, int value) {
    // Buscar en el arr, si existe value
    // devolver True/False.
    for (int i = 0; i < size; i++) {
      if ( *(arr + i) == value) return 1;
    }
    return 0;
}

int* union_operation(int *set_a, int size_a, int *set_b, int size_b) {
  int result[size_a + size_b];
  int count_set_b = 0;

  for(int i = 0; i < size_a; i++) {
    *(result + i) = *(set_a + i);
  }

  for(int i = 0; i < size_b; i++) {
    if(!contains(set_a, size_b, *(set_b + i))) {
       *(result + (size_a + i)) = *(set_b + i);
       count_set_b++;
    }
  }

  for(int i = 0; i<(size_a + count_set_b); i++) {
    printf("%d \n", *(result + i));
  }

  return set_a;
}

int* inserction_operation(int *set_a, int size_a, int *set_b, int size_b) {
  int result[size_a + size_b];
  int count_set_b = 0;

  for(int i = 0; i<size_b; i++) {
    if(contains(set_a, size_a, *(set_b + i))){
      *(result + count_set_b) = *(set_b + i);
      count_set_b ++;
    }
  }

  printf("hola \n");
  for(int i = 0; i<count_set_b; i++) {
    printf("%d \n", *(result + i));
  }

  return set_a;
}

int main () {
    // 1. Entender el problema.
    // 2. Definir dos conjuntos con valores estaticos
    //   2.1 set_a = {1, 2, 4, 5}
    //   2.2 set_b = {3, 6, 4, 5}
    int set_a [] = {1, 2, 4, 5, 9};
    int set_b [] = {3, 6, 4, 5};
    //   2.3 Determinar tamanios arrays
    int size_a = sizeof(set_a) / sizeof(set_a[0]);
    int size_b = sizeof(set_b) / sizeof(set_b[0]);

    if (contains(set_a, size_a, 17))
    {
        printf("Exists.\n");
    } else
    {
        printf("No Exists.\n");
    }



    // 3. Crear una funcion para union
    int* set_union = union_operation(set_a, size_a, set_b, size_b);
    // 4. Crear una funcion para interseccion
    int* set_intersection = inserction_operation(set_a, size_a, set_b, size_b);

    return 0;
}
