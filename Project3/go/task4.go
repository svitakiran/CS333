package main
import "fmt"

func main() {
	fmt.Println("1. if / else if / else")
	if num := 9; num < 0 {
		fmt.Println(num, "negative")
	} else if num < 10 {
		fmt.Println(num, "1 digit")
	} else {
		fmt.Println(num, "multiple digits")
	}

	
	fmt.Println("\n2. for (3 forms)")
	
	fmt.Println("c style loop:")
	for i := 0; i < 3; i++ {
		fmt.Printf("i = %d\n", i)
	}
	
	fmt.Println("while style loop:")
	j := 0
	for j < 3 {
		fmt.Printf("j = %d\n", j)
		j++
	}

	fmt.Println("for range loop:")
	mySlice := []string{"a", "b", "c"}
	for index, value := range mySlice {
		fmt.Printf("index: %d, value: %s\n", index, value)
	}


	fmt.Println("\n3. switch")
	day := "wednesday"
	switch day {
	case "monday", "tuesday", "wednesday", "thursday", "friday":
		fmt.Println(day, "weekday.")
	case "saturday", "sunday":
		fmt.Println(day, "weekend day.")
	default:
		fmt.Println(day, "not a valid day.")
	}


	fmt.Println("\n4. defer")
	defer fmt.Println("prints last right before main exits")
	fmt.Println("prints first")
	fmt.Println("\n5. break and continue")

	OuterLoop:
		for x := 0; x < 3; x++ {
			for y := 0; y < 3; y++ {
				if x == 1 && y == 1 {
					fmt.Println("breaking out of the outerLoop now")
					break OuterLoop
				}
				fmt.Printf("x=%d, y=%d\n", x, y)
			}
		}

}