package main

import (
	"errors"
	"fmt"
	"math"
)

func sum(x int, y int) int {
	return x + y
}

type person struct {
	name string
	age  int
}

func main() {
	var myname string = "Paulo"
	value := sum(10, 15)
	fmt.Println("Hello, ", myname, ": value =", value)
	result, err := sqrt(16)
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Println(result)
	}
	result2, err2 := sqrt(-16)
	if err2 != nil {
		fmt.Println(err2)
	} else {
		fmt.Println(result2)
	}
	p := person{name: "Paulo", age: 50}
	fmt.Println(p)
	testPointer()
}

func sqrt(x float64) (float64, error) {
	if x < 0 {
		return 0, errors.New("undefined for negative numbers")
	}
	return math.Sqrt(x), nil
}

func testPointer() {
	i := 7
	inc(&i)
	fmt.Println(i)
}

func inc(x *int) {
	fmt.Println("Pointer address: ", x)
	*x++
}
