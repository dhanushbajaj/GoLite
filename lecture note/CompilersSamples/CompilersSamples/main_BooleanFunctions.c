#include <stdio.h>

// Lambda:
// TRUE = λx.λy.x
// FALSE = λx.λy.y
// NOT = λx.x FALSE TRUE
// AND = λx.λy. x y FALSE
// OR = λx.λy. x TRUE y
// XOR = λx.λy. x (y FALSE TRUE) y
// IMP = λx.λy. x y TRUE

#define True 1
#define False 0

typedef int (*func_ptr)(int, int);

// Functions for Calls ..............................

int call_func(func_ptr f, int x, int y) {
    return f(x, y);
}

int call_default(func_ptr f) {
    return call_func(f, True, False);
}

// Functions for Constants ..............................

int TRUE(int x, int y) {
    return x;
}

int FALSE(int x, int y) {
    return y;
}

// Unary functions  ..............................

int NOT(func_ptr x) {
    return call_func(x, False, True);
}

// Binary functions  ..............................

int AND(func_ptr x, func_ptr y) {
    return call_func(x, 
        call_default(y), 
        call_default(FALSE));
}

int OR(func_ptr x, func_ptr y) {
    return call_func(x, 
        call_default(TRUE), 
        call_default(y));
}

int XOR(func_ptr x, func_ptr y) {
    return call_func(x, 
        call_func(y, call_default(FALSE), call_default(TRUE)), 
        call_default(y));
}

int IMP(func_ptr x, func_ptr y) {
    return call_func(x, 
        call_default(y), 
        call_default(TRUE));
}

int main_BooleanFunctions() {
    func_ptr t, f;
    int T, F, n, a, o, x, i;
    printf("Constants .................\n");
    t = TRUE;
    T = call_default(t);
    printf("TRUE: %d\n", T);
    f = FALSE;
    F = call_default(f);
    printf("FALSE: %d\n", F);
    printf("Not .......................\n");
    n = NOT(t);
    printf("NOT TRUE: %d\n", n);
    n = NOT(f);
    printf("NOT FALSE: %d\n", n);
    printf("And .......................\n");
    a = AND(t, t);
    printf("TRUE AND TRUE: %d\n", a);
    a = AND(t, f);
    printf("TRUE AND FALSE: %d\n", a);
    a = AND(f, t);
    printf("FALSE AND TRUE: %d\n", a);
    a = AND(f, f);
    printf("FALSE AND FALSE: %d\n", a);
    printf("Or ........................\n");
    o = OR(t, t);
    printf("TRUE OR TRUE: %d\n", o);
    o = OR(t, f);
    printf("TRUE OR FALSE: %d\n", o);
    o = OR(f, t);
    printf("FALSE OR TRUE: %d\n", o);
    o = OR(f, f);
    printf("FALSE OR FALSE: %d\n", o);
    printf("Xor .......................\n");
    x = XOR(t, t);
    printf("TRUE XOR TRUE: %d\n", x);
    x = XOR(t, f);
    printf("TRUE XOR FALSE: %d\n", x);
    x = XOR(f, t);
    printf("FALSE XOR TRUE: %d\n", x);
    x = XOR(f, f);
    printf("FALSE XOR FALSE: %d\n", x);
    printf("Imp .......................\n");
    i = IMP(t, t);
    printf("TRUE IMP TRUE: %d\n", i);
    i = IMP(t, f);
    printf("TRUE IMP FALSE: %d\n", i);
    i = IMP(f, t);
    printf("FALSE IMP TRUE: %d\n", i);
    i = IMP(f, f);
    printf("FALSE IMP FALSE: %d\n", i);
    return 0;
}
