#include <stdio.h>
#include <mpi.h>

#define N 1000000

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int token = 0;

  if(rank == 0) {
    token = 0;

    MPI_Send(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    printf("Proceso 0: envio token inicial = %d\n", token);

    MPI_Recv(&token, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf ("Proceso 0: token de vuelta = %d \n", token);
  } else {
    MPI_Recv(&token, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    token += rank;
    printf("Proceso %d: token recibido, ahora vale %d\n", rank ,token);

    int siguiente = (rank + 1) % size;
    MPI_Send(&token, 1, MPI_INT, siguiente, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}
