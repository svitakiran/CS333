// Implementing a bubble sort algorithm in Go that can be used for any type and to obtain
// any desired order

// Svita Kiran
// CS333
// 10/30/2025


package main

import "fmt"

// bubble sort using comparator function
func bubbleSort[T any](arr []T, comparator func(a, b T) bool) {
	n := len(arr)
	for i := 0; i < n - 1; i++ {
		for j := 0; j < n - i - 1; j++ {
			if comparator(arr[j + 1], arr[j]) {
				arr[j], arr[j+1] = arr[j+1], arr[j]
			}
		}
	}
}

// test program
func main() {
	// int test
	nums := []int{5, 2, 9, 1, 7}
    bubbleSort(nums, func(a, b int) bool { return a < b }) // ascending
    fmt.Println("Sorted ints:", nums)

    // string test
    words := []string{"car", "bike", "train"}
    bubbleSort(words, func(a, b string) bool { return a < b }) // alphabetical
    fmt.Println("Sorted strings:", words)
}