/*
 * How to read from and write to a file in Go
 * 
 * Svita Kiran
 * 11/13/2025
 * CS333
*/

package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
)

func main() {
	file, err := os.Create("gotask4.txt")
	if err != nil {
		fmt.Println("error creating file:", err)
		return
	}
	file.WriteString("This is a file I/O for task 4 with go.\n")
	file.Close()

	f, err := os.Open("gotask4.txt")
	if err != nil {
		fmt.Println("error opening file:", err)
		return
	}
	defer f.Close()

	reader := bufio.NewReader(f)
	fmt.Println("reading file:")
	for {
		line, err := reader.ReadString('\n')
		fmt.Print(line)
		if err == io.EOF {
			break
		}
	}
}
