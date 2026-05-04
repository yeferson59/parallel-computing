#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define N 10000000

/*
 * Author: Yeferson Toloza Contreras
 * Description: Add number partial
 * N = 10.000.000, Result = 50000005000000
 * speedUp = 0.013 / 0.008137 = 1.5976
 * (1 - (1 / 1.5976)) / (1 - (1 / 4)) = 0.4987 = 49.87% Segun la ley de Amdahl simulación en paralelo
 */

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int local_n = N / size;
  int *data = NULL;
  int *local = (int *)malloc(local_n * sizeof(int));

  if(rank == 0) {
    data = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
      *(data + i) = i + 1;
    }
  }

  double t0 = MPI_Wtime();

  MPI_Scatter(data, local_n, MPI_INT, local, local_n, MPI_INT, 0, MPI_COMM_WORLD);

  long add_local = 0;
  for (int i = 0; i < local_n; i++) {
    add_local += *(local + i);
  }

  printf("Proceso %d: suma parcial = %ld \n", rank, add_local);

  long total = 0;

  MPI_Reduce(&add_local, &total, 1, MPI_LONG, MPI_SUM, 0,MPI_COMM_WORLD);

  double t1 = MPI_Wtime();

  if(rank == 0){
    printf("\nSuma total = %ld (esperado : %ld)\n", total , (long) N * (N + 1) / 2);
    printf("Tiempo paralelo : %.6f segundos \n", t1 - t0 ) ; // 0.008137
    free(data);
  }

  free(local);
  MPI_Finalize();
  return 0;
}
