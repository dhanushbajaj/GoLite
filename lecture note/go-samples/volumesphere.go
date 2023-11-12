package main

import (
	"fmt"
	"math"
)

func sphereVolume(radius float64) float64 {
	return (4.0 / 3.0) * math.Pi * math.Pow(radius, 3)
}

func main() {
	radius := 5.0 // Replace this with the desired radius
	volume := sphereVolume(radius)
	//fmt.Printf("Volume of the sphere with radius %.2f is %.2f\n", radius, volume)
	fmt.Println("Volume of the sphere with radius", radius, " is ", volume)

}