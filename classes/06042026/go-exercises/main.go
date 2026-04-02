package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const N = 10_000_000

func Sequential() float64 {
	arr := make([]int, N)

	t0 := time.Now()

	for i := range N {
		arr[i] = rand.Intn(200)
	}

	t1 := time.Since(t0)

	return t1.Seconds()
}

func Parallel() float64 {
	var wg sync.WaitGroup
	arr := make([]int, N)

	tp0 := time.Now()

	wg.Go(func() {
		for i := range N {
			arr[i] = rand.Intn(200)
		}
	})

	wg.Wait()

	tp1 := time.Since(tp0)

	fmt.Println(arr)

	return tp1.Seconds()
}

func ParallelWithThreads() float64 {
	var wg sync.WaitGroup
	totalThreads := 12
	chunckSize := N / totalThreads
	arr := make([]int, N)

	tp0 := time.Now()
	for i := range totalThreads {
		wg.Go(func() {
			start := i * chunckSize
			end := start + chunckSize
			if (i + 1) == totalThreads {
				end = N
			}

			for j := start; j < end; j++ {
				arr[j] = rand.Intn(200)
			}
		})
	}

	wg.Wait()

	tp1 := time.Since(tp0)

	return tp1.Seconds()
}

func main() {
	timeSeq := Sequential()

	timePar1 := Parallel()

	timePar2 := ParallelWithThreads()

	fmt.Println(timeSeq, timePar1, timePar2)

	speedUp := timeSeq / timePar1
	speedUp2 := timeSeq / timePar2

	fmt.Println(speedUp)
	fmt.Println(speedUp2)

	porcentParallel := (1 - (1 / speedUp)) / (1 - (1 / 2.0))
	porcentParallel2 := (1 - (1 / speedUp2)) / (1 - (1 / 12.0))

	fmt.Println(porcentParallel)
	fmt.Println(porcentParallel2)
}
