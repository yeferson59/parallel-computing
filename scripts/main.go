package main

import (
	"fmt"
	"log"
	"os/exec"
	"strconv"
	"strings"
)

func ExecuteFile(path string, filename string, outputFilename string, typeCode string) {
	if typeCode == "parallel" {
		if err := exec.Command("gcc-15", "-fopenmp", path+"/"+filename, "-o", outputFilename).Run(); err != nil {
			log.Fatal(err)
		}
	} else {
		if err := exec.Command("gcc-15", path+"/"+filename, "-o", outputFilename).Run(); err != nil {
			log.Fatal(err)
		}
	}
}

func GetTime(path string, filename string) float64 {
	cmd := exec.Command(path + "/" + filename)

	output, err := cmd.Output()
	if err != nil {
		log.Fatal(err)
	}

	data := string(output)
	timeStr := strings.Split(data, " ")[6]
	time, _ := strconv.ParseFloat(timeStr, 64)
	return time
}

func GetTimeWithThreads(path string, filename string, numThreads int) float64 {
	cmd := exec.Command("sh", "-c", "export OMP_NUM_THREADS="+strconv.Itoa(numThreads)+" && "+path+"/"+filename)

	output, err := cmd.Output()
	if err != nil {
		log.Fatal(err)
	}

	data := string(output)
	timeStr := strings.Split(data, " ")[6]
	time, _ := strconv.ParseFloat(timeStr, 64)
	return time
}

func main() {
	pathSequential, filenameSequential := "./classes/06042026/c-exercises", "cb_ejercicio1_seq.c"
	pathParallel, filenameParallel := "./classes/06042026/openmp", "omp_ejercicio1_par.c"

	ExecuteFile(pathSequential, filenameSequential, "a.out", "sequential")
	ExecuteFile(pathParallel, filenameParallel, "a.out", "parallel")

	sequentialTime := GetTime(pathSequential, "a.out")
	parallelTime := GetTime(pathParallel, "a.out")

	speedup := sequentialTime / parallelTime
	fmt.Println(speedup)

	porcentageParallel := (1 - (1 / speedup)) / (1 - (1 / 8.0))
	fmt.Println(porcentageParallel)

	fmt.Println("with differents threads")
	for i := range 12 {
		threads := i + 1
		parallelTime := GetTimeWithThreads(pathParallel, "a.out", threads)
		speedup := sequentialTime / parallelTime
		fmt.Println("Threads:", threads, "Speedup:", speedup)

		porcentageParallel := (1 - (1 / speedup)) / (1 - (1 / 8.0))
		fmt.Println("Porcentage Parallel:", porcentageParallel)
	}
}
