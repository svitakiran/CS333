package main
import "fmt"

var packageScope = "visible to package"
var exportedVar = "visible outside package"
var unexportedVar = "only visible inside package"

func main() {
	var functionScope = "visible inside main()"
	fmt.Println(functionScope)
	fmt.Println(packageScope)
	fmt.Println(exportedVar)
	
	i := 100
	if i > 50 {
		blockScope := "visible inside this if block"
		fmt.Println(blockScope)
	}
}