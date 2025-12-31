package main
import "fmt"

func binarySearch(sortedList []int, target int)(int, bool) {
	low := 0
	high := len(sortedList) - 1

	for low <= high {
		mid := low + (high - low) / 2

		if sortedList[mid] == target {
			return mid, true
		} else if sortedList[mid] < target {
			low = mid + 1
		} else {
			high = mid - 1
		}
	}

	return -1, false
}

func main() {
	data := []int{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}
	target := 11

	fmt.Printf("looking for %d in list: %v\n", target, data)

	idx, found := binarySearch(data, target)
	if found {
		fmt.Printf("target %d found at index %d\n", target, idx)
	} else {
		fmt.Printf("target %d not found in list\n", target)
	}
}