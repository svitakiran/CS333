package main
import "fmt"
import "reflect"

type Car struct {
	Make string
	Model string
	Year int
}

func main() {
	var int1 int = 10
	var int2 int = 3

	var float1 float64 = 10.5
	var float2 float64 = 2.5

	var langGo bool = true

	var greeting string = "hello"
	var world string = "world"

	fmt.Println("integer operations:")
	sum := int1 + int2
	//diff := int1 - int2
	//prod := int1 * int2
	quotient := int1 / int2
	remainder := int1 % int2
	fmt.Printf("%d + %d = %d (type: %s)\n", int1, int2, sum, reflect.TypeOf(sum))
	fmt.Printf("%d / %d = %d (integer division)\n", int1, int2, quotient)
	fmt.Printf("%d %% %d = %d\n", int1, int2, remainder)

	fmt.Println("\nfloat operations:")
	floatSum := float1 + float2
	floatQuotient := float1 / float2
	fmt.Printf("%.1f + %.1f = %.1f (Type: %s)\n", float1, float2, floatSum, reflect.TypeOf(floatSum))
	fmt.Printf("%.1f / %.1f = %.1f\n", float1, float2, floatQuotient)

	fmt.Println("\nstring operations:")
	concatenated := greeting + world
	fmt.Printf("'%s' + '%s' = '%s' (type: %s)\n", greeting, world, concatenated, reflect.TypeOf(concatenated))
	
	fmt.Println("\nboolean operations:")
	fmt.Printf("langGo is %t (type: %s)\n", langGo, reflect.TypeOf(langGo))

	fmt.Println("\ntype system:")
	var mixSum = float64(int1) + float1
	fmt.Printf("float64(%d) + %.1f = %.1f (type: %s)\n", int1, float1, mixSum, reflect.TypeOf(mixSum))

	fmt.Println("\nconstructing aggregate types")
	myCar := Car {
		Make:  "Toyota",
		Model: "Camry",
		Year:  2025,
	}
	fmt.Printf("my car: %+v (type: %s)\n", myCar, reflect.TypeOf(myCar))

	var numbers []int
	numbers = append(numbers, 10)
	numbers = append(numbers, 20)
	fmt.Printf("my numbers slice: %v (type: %s)\n", numbers, reflect.TypeOf(numbers))



}