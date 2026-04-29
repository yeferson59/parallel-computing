#include <stdio.h>
#include <mpi.h>


int main(int argc, char **argv) {
  int rank;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int n = 0;

  if(rank == 0) {
    n = 1000000;
    printf ("Proceso 0: difundiendo N = %d \n", n);
  }

  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

  printf ("Proceso %d: recibi N = %d \n", rank, n) ;

  MPI_Finalize();
  return 0;
}
