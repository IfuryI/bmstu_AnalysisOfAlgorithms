package main

import (
	"math/rand"
	"testing"
	"time"
)

func actionTest(source <-chan int, name string, f actionFunc) <-chan int {
	result := make(chan int)

	go func() {
		defer close(result)

		for arg := range source {
			value := f(arg)
			result <- value
		}
	}()

	return result
}

func generateTest(n int) <-chan int {
	queue := make(chan int)

	go func() {
		defer close(queue)

		for i := 0; i < n; i++ {
			value := rand.Intn(100)
			queue <- value
		}
	}()

	return queue
}

func getStepA(d time.Duration) actionFunc {
	return func(arg int) int {
		time.Sleep(d)
		return arg * arg
	}
}

func benchmarkLinear(count int, b *testing.B) {
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		for i := 0; i < count; i++ {
			var res = rand.Intn(100)
			res = stepA(res)
			res = stepB(res)
			res = stepC(res)
		}
	}
}

func benchmarkConveyor(count int, fStepA actionFunc, b *testing.B) {
	b.ResetTimer()
	for i := 0; i < b.N; i++ {

		var queue = generateTest(count)
		queue = actionTest(queue, "A", fStepA)
		queue = actionTest(queue, "B", stepB)
		queue = actionTest(queue, "C", stepC)
		for res := range queue {
			res = 0 - res
		}
	}
}

func BenchmarkLinear1(b *testing.B)  { benchmarkLinear(1, b) }
func BenchmarkLinear2(b *testing.B)  { benchmarkLinear(2, b) }
func BenchmarkLinear4(b *testing.B)  { benchmarkLinear(4, b) }
func BenchmarkLinear8(b *testing.B)  { benchmarkLinear(8, b) }
func BenchmarkLinear16(b *testing.B) { benchmarkLinear(16, b) }
func BenchmarkLinear32(b *testing.B) { benchmarkLinear(32, b) }

func BenchmarkConveyor1(b *testing.B)  { benchmarkConveyor(1, stepA, b) }
func BenchmarkConveyor2(b *testing.B)  { benchmarkConveyor(2, stepA, b) }
func BenchmarkConveyor4(b *testing.B)  { benchmarkConveyor(4, stepA, b) }
func BenchmarkConveyor8(b *testing.B)  { benchmarkConveyor(8, stepA, b) }
func BenchmarkConveyor16(b *testing.B) { benchmarkConveyor(16, stepA, b) }
func BenchmarkConveyor32(b *testing.B) { benchmarkConveyor(32, stepA, b) }

func BenchmarkConveyor32Sleep200(b *testing.B)  { benchmarkConveyor(32, getStepA(1*time.Second), b) }
func BenchmarkConveyor32Sleep300(b *testing.B)  { benchmarkConveyor(32, getStepA(2*time.Second), b) }
func BenchmarkConveyor32Sleep500(b *testing.B)  { benchmarkConveyor(32, getStepA(5*time.Second), b) }
func BenchmarkConveyor32Sleep1000(b *testing.B) { benchmarkConveyor(32, getStepA(10*time.Second), b) }
func BenchmarkConveyor32Sleep5000(b *testing.B) { benchmarkConveyor(32, getStepA(20*time.Second), b) }
