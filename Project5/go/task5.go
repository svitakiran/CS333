/*
 * Program that automatically detects garbage collections from the timing information
 in Go (Go has automatic memory management)
 * 
 * Svita Kiran
 * 11/13/2025
 * CS333
*/

package main

import (
    "fmt"
    "time"
)

func allocateMemory() {
    _ = make([]int, 10_000_000)
}

func main() {
    const runs = 100
    times := make([]time.Duration, runs)

    for i := 0; i < runs; i++ {
        start := time.Now()
        allocateMemory()
        elapsed := time.Since(start)
        times[i] = elapsed
    }

    var total time.Duration
    for _, t := range times {
        total += t
    }
    avg := total / runs

    fmt.Printf("average time: %v\n", avg)

    for i, t := range times {
        if t > 2*avg {
            fmt.Printf("long run #%d: %v\n", i+1, t)
        }
    }
}
