package main

import "fmt"

// Function that takes two integers and applies a binary operation on them
type BinaryOperation func(int, int) int

func add(a, b int) int {
	return a + b
}

func subtract(a, b int) int {
	return a - b
}

func applyOperation(op BinaryOperation, a, b int) int {
	return op(a, b)
}

func main() {
	// Store the 'add' function in a variable
	var addFunc BinaryOperation = add

	// Call the function through the variable
	result := addFunc(3, 4)
	fmt.Println("Result of add:", result) // Output: Result of add: 7

	// Store the 'subtract' function in the same variable
	addFunc = subtract

	// Call the function through the same variable
	result = addFunc(10, 5)
	fmt.Println("Result of subtract:", result) // Output: Result of subtract: 5

	// Using the applyOperation function to apply any binary operation
	result = applyOperation(add, 2, 3)
	fmt.Println("Result of applyOperation (add):", result) // Output: Result of applyOperation (add): 5

	result = applyOperation(subtract, 8, 3)
	fmt.Println("Result of applyOperation (subtract):", result) // Output: Result of applyOperation (subtract): 5
}
