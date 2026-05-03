#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <math.h>

#define N_TOTAL 10000000L

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  long n_local = N_TOTAL / size;

  srand(12345 + rank * 1000);

  double t0 = MPI_Wtime();

  long dentro_local = 0;
  for(long i = 0; i < n_local; i++) {
    double x = (double) rand() / RAND_MAX;
    double y = (double) rand() / RAND_MAX;
    if (x * x + y * y <= 1.0) {
      dentro_local++;
    }
  }

  printf("Proceso %d: %ld puntos dentro de %ld totales\n", rank, dentro_local, n_local);

  long dentro_total = 0;
  MPI_Reduce(&dentro_local, &dentro_total, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

  double t1 = MPI_Wtime();

  if(rank == 0) {
    double pi_est = 4.0 * (double)dentro_total / (double) N_TOTAL;
    printf("\nPuntos totales: %ld \n", N_TOTAL);
    printf("Dentro del circulo: %ld \n" , dentro_total);
    printf("PI estimado: %.8f \n" , pi_est);
    printf("PI real: %.8f \n", M_PI);
    printf("Error: %.8f \n" , fabs(pi_est - M_PI));
    printf("Tiempo: %.4fs | Procesos: %d \n", t1 - t0, size);
  }

  MPI_Finalize();
  return 0;
}
