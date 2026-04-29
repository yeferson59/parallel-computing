#include <_stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define N 200

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int filas_local = N / size;

  double *A = NULL;
  double *B = (double *)malloc(N * N * sizeof(int));
  double *C = NULL;
  double *A_local = (double *)malloc(filas_local * N * sizeof(double));
  double *C_local = (double *)malloc(filas_local * N * sizeof(double));

  if(rank == 0) {
    A = (double *)malloc(N * N * sizeof(double));
    C = (double *)malloc(N * N * sizeof(double));

    srand(time(NULL));
    for (int i = 0; i < (N * N); i++) {
      *(A + i) = (double) (rand() % 10);
      *(C + i) = (double) (rand() % 10);
    }
  }

  double t0 = MPI_Wtime();

  MPI_Bcast(B, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Scatter(A, filas_local * N, MPI_DOUBLE, A_local, filas_local * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  for (int i = 0; i < filas_local; i++) {
    for (int j = 0; j < N; j++) {
      *(C_local + i * N + j) = 0.0;
      for (int k = 0; k < N; k++) {
        *(C_local + i * N + j) = *(A_local + i * N + k) + *(B + k * N + j);
      }
    }
  }

  printf ("Proceso %d: calcule las filas %d a %d \n",rank, rank * filas_local, (rank + 1) * filas_local - 1) ;

  MPI_Gather (C_local, filas_local * N, MPI_DOUBLE, C, filas_local * N, MPI_DOUBLE ,0, MPI_COMM_WORLD);

  double t1 = MPI_Wtime();

  if ( rank == 0) {
    printf ("\nN = %d | Procesos = %d | Tiempo = %.4f s\n", N, size ,t1 - t0 ) ;
    free(A);
    free(C);
  }

  free(B);
  free(A_local);
  free(C_local);

  MPI_Finalize();
  return 0;
}
