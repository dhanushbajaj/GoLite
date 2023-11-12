package main

import "fmt"

type func_ptr func(int, int) int

/* Functions for Calls ................. */

func call_func(op func_ptr, a, b int) int {
	return op(a, b)
}

func call_default(f func_ptr) int {
    return call_func(f, 1, 0);
}

/* Functions for Constants …............ */

func TRUE(x int, y int) int {
	return x
}

func FALSE(x int, y int) int {
	return y
}

/* Unary functions ..................... */

func NOT(x func_ptr) int {
    return call_func(x, 0, 1);
}

/* Binary functions .................... */

func AND(x func_ptr, y func_ptr) int {
    return call_func(x, 
        call_default(y), 
        call_default(FALSE));
}

func OR(x func_ptr, y func_ptr) int {
    return call_func(x, 
        call_default(TRUE), 
        call_default(y));
}

func XOR(x func_ptr, y func_ptr) int {
    return call_func(x, 
        call_func(y, 
             call_default(FALSE),
             call_default(TRUE)), 
        call_default(y));
}

func IMP(x func_ptr, y func_ptr) int {
    return call_func(x, 
        call_default(y), 
        call_default(TRUE));
}

/* Main function .................... */

func main() {
    t, f := TRUE, FALSE;
    T, F, n, a, o, x, i := 0, 0, 0, 0, 0, 0, 0;

    fmt.Println("Constants .................");
    t = TRUE;
    T = call_default(t);
    fmt.Println("TRUE: ", T);
    f = FALSE;
    F = call_default(f);
    fmt.Println("FALSE: ", F);
    fmt.Println("Not .......................");
    n = NOT(t);
    fmt.Println("NOT TRUE: ", n);
    n = NOT(f);
    fmt.Println("NOT FALSE: ", n);
    fmt.Println("And .......................");
    a = AND(t, t);
    fmt.Println("TRUE AND TRUE: ", a);
    a = AND(t, f);
    fmt.Println("TRUE AND FALSE: ", a);
    a = AND(f, t);
    fmt.Println("FALSE AND TRUE: ", a);
    a = AND(f, f);
    fmt.Println("FALSE AND FALSE: ", a);
    fmt.Println("Or ........................");
    o = OR(t, t);
    fmt.Println("TRUE OR TRUE: ", o);
    o = OR(t, f);
    fmt.Println("TRUE OR FALSE: ", o);
    o = OR(f, t);
    fmt.Println("FALSE OR TRUE: ", o);
    o = OR(f, f);
    fmt.Println("FALSE OR FALSE: ", o);
    fmt.Println("Xor .......................");
    x = XOR(t, t);
    fmt.Println("TRUE XOR TRUE: ", x);
    x = XOR(t, f);
    fmt.Println("TRUE XOR FALSE: ", x);
    x = XOR(f, t);
    fmt.Println("FALSE XOR TRUE: ", x);
    x = XOR(f, f);
    fmt.Println("FALSE XOR FALSE: ", x);
    fmt.Println("Imp .......................");
    i = IMP(t, t);
    fmt.Println("TRUE IMP TRUE: ", i);
    i = IMP(t, f);
    fmt.Println("TRUE IMP FALSE: ", i);
    i = IMP(f, t);
    fmt.Println("FALSE IMP TRUE: ", i);
    i = IMP(f, f);
    fmt.Println("FALSE IMP FALSE: ", i);
}
