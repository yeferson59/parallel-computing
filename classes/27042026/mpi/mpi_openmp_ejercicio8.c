#include <mpi.h>
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 10000000L // 10 millones de elementos

int main(int argc, char **argv) {
  int provided;
  MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  long n_local = N / size ;
  double * datos = ( double *) malloc ( n_local * sizeof ( double ) ) ;

  for (long i = 0; i < n_local; i ++) {
    datos [ i ] = ( double ) ( rank * n_local + i + 1) ;
  }

  double t0 = MPI_Wtime();

  double suma_local = 0.0;
  int num_hilos;

  #pragma omp parallel reduction (+:suma_local)
  {
    #pragma omp single
    num_hilos = omp_get_num_threads();
    #pragma omp for
    for(long i = 0; i < n_local; i++) {
      suma_local += *(datos + i);
    }
  }

  printf("Proceso %d (usando %d hilos OMP): suma_local = %.0f\n", rank, num_hilos, suma_local);

  double suma_total = 0.0;
  MPI_Reduce(&suma_local, &suma_total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  double t1 = MPI_Wtime();

  if(rank == 0) {
    double esperado = (double) N * (N + 1) / 2.0;
    printf("\nSuma total = %.0f \n " , suma_total);
    printf("Esperado = %.0f\n", esperado);
    printf("Tiempo = %.4fs\n", t1 - t0);
    printf("Config = %d procesos MPI x %d hilos OpenMP\n", size, num_hilos);
  }

  free(datos);
  MPI_Finalize();
  return 0;
}
