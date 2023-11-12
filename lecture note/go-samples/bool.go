package main

import "fmt"

const True = 1
const False = 0

type funcType func(x, y int) int

func TRUE(x, y int) int {
    return x
}

func FALSE(x, y int) int {
    return y
}

func callFunc(f funcType, x, y int) int {
    return f(x, y)
}

func callDefault(f funcType) int {
    return callFunc(f, True, False)
}

func NOT(x funcType) int {
    return callFunc(x, False, True)
}

func AND(x, y funcType) int {
    return callFunc(x, callDefault(y), callDefault(FALSE))
}

func OR(x, y funcType) int {
    return callFunc(x, callDefault(TRUE), callDefault(y))
}

func XOR(x, y funcType) int {
    return callFunc(x, callFunc(y, callDefault(FALSE), callDefault(TRUE)), callDefault(y))
}

func IMP(x, y funcType) int {
    return callFunc(x, callDefault(y), callDefault(TRUE))
}

func boolean() {
    var t, f funcType
    var T, F, n, a, o, x, i int
    fmt.Println("Constants .................")
    t = TRUE
    T = callDefault(t)
    fmt.Printf("TRUE: %d\n", T)
    f = FALSE
    F = callDefault(f)
    fmt.Printf("FALSE: %d\n", F)
    fmt.Println("Not .......................")
    n = NOT(t)
    fmt.Printf("NOT TRUE: %d\n", n)
    n = NOT(f)
    fmt.Printf("NOT FALSE: %d\n", n)
    fmt.Println("And .......................")
    a = AND(t, t)
    fmt.Printf("TRUE AND TRUE: %d\n", a)
    a = AND(t, f)
    fmt.Printf("TRUE AND FALSE: %d\n", a)
    a = AND(f, t)
    fmt.Printf("FALSE AND TRUE: %d\n", a)
    a = AND(f, f)
    fmt.Printf("FALSE AND FALSE: %d\n", a)
    fmt.Println("Or .......................")
    o = OR(t, t)
    fmt.Printf("TRUE OR TRUE: %d\n", o)
    o = OR(t, f)
    fmt.Printf("TRUE OR FALSE: %d\n", o)
    o = OR(f, t)
    fmt.Printf("FALSE OR TRUE: %d\n", o)
    o = OR(f, f)
    fmt.Printf("FALSE OR FALSE: %d\n", o)
    fmt.Println("Xor .......................")
    x = XOR(t, t)
    fmt.Printf("TRUE XOR TRUE: %d\n", x)
    x = XOR(t, f)
    fmt.Printf("TRUE XOR FALSE: %d\n", x)
    x = XOR(f, t)
    fmt.Printf("FALSE XOR TRUE: %d\n", x)
    x = XOR(f, f)
    fmt.Printf("FALSE XOR FALSE: %d\n", x)
    fmt.Println("Imp .......................")
    i = IMP(t, t)
    fmt.Printf("TRUE IMP TRUE: %d\n", i)
    i = IMP(t, f)
    fmt.Printf("TRUE IMP FALSE: %d\n", i)
    i = IMP(f, t)
    fmt.Printf("FALSE IMP TRUE: %d\n", i)
    i = IMP(f, f)
    fmt.Printf("FALSE IMP FALSE: %d\n", i)
}

func main() {
    boolean()
}
