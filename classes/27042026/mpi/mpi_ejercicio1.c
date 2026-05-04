#include <mpi.h>
#include <stdio.h>

/*
 * Author: Yeferson Toloza Contreas
 * Description: hello world for simple program MPI
 * Questions:
 * ¿Cambia el orden de los mensajes al ejecutar varias veces? ¿Por qué?
 * Sí cambia el orden de impresión del proceso, porque dependiendo de como el sistema operativo esta ejecutando proceso y tenga nucleos disponibles se lo envia al programa de ejecucíon.
 * ¿Qué ocurre si lanzas el programa con -n 1?
 * Al lanzar el programa con -n = 1 se imprime un size de 1 y el 0 proceso.
 */

int main(int argc, char **argv) {
  int size, rank;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  printf ("Hola, soy el proceso %d de %d procesos en total.\n", rank, size) ;

  MPI_Finalize();

  return 0;
}
