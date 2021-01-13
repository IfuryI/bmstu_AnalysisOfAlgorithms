package main

import (
	"fmt"
	"math/rand"
	"os"
	"time"
)

func getTime() string {
	return time.Now().Format("15:04:05.99999999")
}

type actionFunc func(int) int

func action(source <-chan int, name string, f actionFunc) <-chan int {
	result := make(chan int)

	go func() {
		defer close(result)

		for arg := range source {
			fmt.Print("time: ", getTime(), " in  ", name, ": ", arg, "\n")
			value := f(arg)
			fmt.Print("time: ", getTime(), " out ", name, ": ", value, "\n")
			result <- value
		}
	}()

	return result
}

func linearAction(arg int, name string, f actionFunc) int {
	fmt.Print("time: ", getTime(), " in  ", name, ": ", arg, "\n")
	value := f(arg)
	fmt.Print("time: ", getTime(), " out ", name, ": ", value, "\n")

	return value
}

func generate(n int) <-chan int {
	queue := make(chan int)

	go func() {
		defer close(queue)

		for i := 0; i < n; i++ {
			value := rand.Intn(100)
			fmt.Print("time: ", getTime(), " send: ", value, "\n")
			queue <- value
		}
	}()

	return queue
}

func linearGenerate() int {
	value := rand.Intn(100)
	fmt.Print("time: ", getTime(), " send: ", value, "\n")
	return value
}

func stepA(arg int) int {
	time.Sleep(100)
	return arg * arg
}

func stepB(arg int) int {
	time.Sleep(200)
	return arg * arg
}

func stepC(arg int) int {
	time.Sleep(150)
	return arg * arg
}

func conveyorRun(count int) {
	var queue = generate(count)
	queue = action(queue, "A", stepA)
	queue = action(queue, "B", stepB)
	queue = action(queue, "C", stepC)

	for res := range queue {
		fmt.Print("time: ", getTime(), " res: ", res, "\n")
	}
}

func main() {
	var count int
	fmt.Print("Enter generate count: ")
	_, err := fmt.Scanf("%d", &count)
	if err != nil {
		fmt.Println(err)
		os.Exit(-1)
	}

	conveyorRun(count)
}
