#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
  int rank;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int number = 77;

  if(rank == 0) {
    MPI_Send(&number, 1, MPI_INT, 1, 42, MPI_COMM_WORLD);

    printf("Proceso 0: envie el numero %d al proceso 1. \n", number);

    MPI_Status status;

    MPI_Recv(&number, 1, MPI_INT, 1, 41, MPI_COMM_WORLD, &status);

    printf("Proceso 0: recibio el numero %d del proceso 1. \n", number);
  }

  if(rank == 1) {
    MPI_Status status;

    MPI_Recv(&number, 1, MPI_INT, 0, 42, MPI_COMM_WORLD, &status);

    printf("Proceso 1: recibi el numero %d del proceso 0. \n", number);

    number *= 2;

    MPI_Send(&number, 1, MPI_INT, 0, 41, MPI_COMM_WORLD);

    printf("Proceso 1: envia el numero %d al proceso 0. \n", number);
  }

  MPI_Finalize();
  return 0;
}
