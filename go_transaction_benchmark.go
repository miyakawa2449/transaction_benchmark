package main

import (
	"fmt"
	"sync"
	"time"
)

func processTransaction(id int) {
	// 模擬トランザクション処理
	_ = id * 2
}

func main() {
	var wg sync.WaitGroup
	start := time.Now()

	transactionCount := 100000
	wg.Add(transactionCount)

	for i := 0; i < transactionCount; i++ {
		go func(id int) {
			defer wg.Done()
			processTransaction(id)
		}(i)
	}

	wg.Wait()
	fmt.Printf("Completed %d transactions in %v\n", transactionCount, time.Since(start))
}