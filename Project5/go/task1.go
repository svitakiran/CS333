/*
 * Error handling in Go
 * 
 * Svita Kiran
 * 11/13/2025
 * CS333
*/

package main

import (
    "errors"
    "fmt"
    "os"
)

func openFileDemo() {
    fmt.Println("file I/O error")

    file, err := os.Open("dne.txt")
    if err != nil {
        fmt.Println("Error opening file:", err)
        return
    }
    defer file.Close()

    fmt.Println("file opened")
}

func safeDivide(a, b int) (int, error) {
    if b == 0 {
        return 0, errors.New("cant divide by zero")
    }
    return a / b, nil
}

func divideDemo() {
    fmt.Println("\ndivision error")

    _, err := safeDivide(10, 0)
    if err != nil {
        fmt.Println("error:", err)
        return
    }
}

func main() {
    openFileDemo()
    divideDemo()
}
