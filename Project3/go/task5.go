package main
import "fmt"

func applyOperation(a int, b int, op func(int, int) int) int {
	fmt.Printf("applying operation to %d and %d\n", a, b)
	return op(a, b)
}

func add(x, y int) int {
	return x + y
}

func main() {
	var mathOp func(int, int) int
	mathOp = add
	result1 := mathOp(10, 5)
	fmt.Printf("result of assigning 'add' to a variable: %d\n\n", result1)

	multiply := func(x, y int) int {
		return x * y
	}
	result2 := multiply(10, 5)
	fmt.Printf("result of an anonymous 'multiply' function: %d\n\n", result2)

	result3 := applyOperation(20, 8, add)
	fmt.Printf("result of passing 'add' to another function: %d\n\n", result3)

	result4 := applyOperation(20, 8, multiply)
	fmt.Printf("result of passing 'multiply' to another function: %d\n\n", result4)

	result5 := applyOperation(20, 8, func(x, y int) int {
		return x - y
	})
	fmt.Printf("result of passing a new anonymous function: %d\n", result5)
}