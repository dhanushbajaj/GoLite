// Complex C declarations - reading and writing
//  Pointers to functions, array of pointer to functions 
//  Author: Svillen Ranev / Paulo Sousa

// STARTING IN ONE MIN... Welcome everyone to practice.
#include <stdio.h>

// function declarations - protopypes
float add (float a, float b);
float sub (float a, float b);
float mul (float a, float b);
float div (float a, float b);
// Function 5: Greater value
float greater(float a, float b);
// Function 6: Mean 
float mean(float a, float b);
// pointer to function taking two ints and returning int
typedef float (*PTR_F)(float,float); // PTR_F is the new data type name

// Main function to use function pointers
int main_FunctionPointers (void) {
	// pointer to function taking two ints and returning int
	float (*ptr_f)(float,float);
	PTR_F ptr_ft; // same as above

	// array of pointer to function
	#define numOfFunc 6
	float (*aptr_f[numOfFunc])(float,float);
	PTR_F aptr_ft[numOfFunc]; // same as above

	/* Initialization or assignment */
	ptr_f = ptr_ft = mul;
	aptr_f[0] = aptr_ft[0] = add;
	aptr_f[1] = aptr_ft[1] = sub;
	aptr_f[2] = aptr_ft[2] = mul;
	aptr_f[3] = aptr_ft[3] = div;
	aptr_f[4] = aptr_ft[4] = greater;
	aptr_f[5] = aptr_ft[5] = mean;

	/* function call */
	float a = 3.0f, b = 2.0f;
	printf("Mul1: %f\n", (*ptr_f)     (a, b));			// calls add()
	printf("Mul2: %f\n", ptr_f        (a, 1.0f));		// ANSI standard extension
	printf("Mul3: %f\n", (*ptr_ft)    (a, (float)1));	// calls add(2.2)
	printf("Add1: %f\n", (*aptr_f[0]) (a, (float)'2')); // calls add()
	printf("Add2: %f\n", aptr_f[0]    (3, 2.0));		// ANSI extension
	printf("Sub: %f\n",  aptr_ft[1]    (a,b));			// calls sub()
	printf("Mul: %f\n",  aptr_ft[2]    (a,b));			// calls mul()
	printf("Div1: %f\n",  aptr_ft[3]    (a,b));			// calls div()
	printf("Div2: %f\n",  aptr_ft[3]('2', 0));			// calls div()
	// Test the Greater passing a and b
	printf("Greater: %f\n", aptr_ft[4]    (a,b));		// calls div()
	// Test the Mean passing a and b
	printf("Mean: %f\n",  aptr_ft[5]    (a,b)); 
	// 2DO: DIV
	return 0;
}
// function definitions
float add (float a, float b) { return a+b; }
float sub (float a, float b) { return a-b; }
float mul (float a, float b) { return a*b; }
float div (float a, float b) { return a/b; }
float greater(float a, float b) { if (a > b) { return a; } return b; }

float mean(float a, float b) {
	return (a + b) / 2;
}
