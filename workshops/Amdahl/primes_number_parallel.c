#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define N 50000
// Function to check if number is prine

int isPrime(int n) {
  if (n < 2) return 0;

  for (int i = 2; i <=sqrt(n); i++) {
    if (n % i == 0)
      return 0;
  }
  return 1;
}

int main() {
  double startTime = omp_get_wtime();
  int counterPrimes = 0;

  // Parallelize loop for search primes
  #pragma omp parallel for reduction(+:counterPrimes)
  for (int i = 2; i <= N; i++) {
    if (isPrime(i)) counterPrimes++;
  }

  double elapsedTime = omp_get_wtime() - startTime;

  printf("Primes found: %d\n", counterPrimes);
  printf("Parallel Time: %.3fsg\n", elapsedTime);
}

// Execution: OMP_NUM_THREADS=6 ./primes_number_parallel


/*
  Mi equipo es un Apple MacBook con chip M1. Usando el comando sysctl hw.physicalcpu hw.logicalcpu en macOS (equivalente al comando de PowerShell solicitado), obtengo 8 núcleos físicos y 8 procesadores lógicos.
   En este caso los valores son iguales porque el M1 no utiliza Hyper-Threading. El Hyper-Threading es una tecnología de Intel mediante la cual un solo núcleo físico puede gestionar 2 hilos de ejecución simultáneamente, apareciendo ante el sistema operativo como 2 procesadores lógicos. Esto permite aprovechar ciclos ociosos del núcleo para ejecutar instrucciones de un segundo hilo. En el M1, en cambio, Apple prefirió incluir más núcleos físicos reales (diferenciados en alto rendimiento y eficiencia energética) sin necesidad de HT.
 */
