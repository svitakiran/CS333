/*
 * Memory management in Go
 * 
 * Svita Kiran
 * 11/13/2025
 * CS333
*/

package main

import "fmt"

type Node struct {
    Value int
    Next  *Node
}

func makeGarbage() {
    head := &Node{1, nil}
    for i := 2; i <= 10; i++ {
        head = &Node{i, head}
    }

    head = nil
}

func main() {
    fmt.Println("creating garbage")
    for i := 0; i < 5; i++ {
        makeGarbage()
    }
    fmt.Println("done and garbage collection will run automatically")
}
