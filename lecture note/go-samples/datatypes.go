package main

import (
	"fmt"
	"reflect"
)

func main() {
	var countryName = "Bulgary"
	var foundationYear = -7000
	var area = 492.0
	fmt.Println("countryName datatype: ",reflect.TypeOf(countryName))
	fmt.Println("foundationYear datatype: ",reflect.TypeOf(foundationYear))
	fmt.Println("area datatype: ",reflect.TypeOf(area))
	fmt.Println(countryName, " was founded in: ", foundationYear, " and has ", area, " km2 area.")
}
