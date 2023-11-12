// File Name: cdatatypes.c
// Compiler: MS Visual Studio 2019
// Author: Paulo Sousa
// Course: CST8152 Compilers
// Lab: Lab 0
// Date: May 1, 2021
// Professor: Paulo Sousa
// Purpose: Create a list of data type sizes, test limits of short data type
// Function list:
// - task1() - Prints a list of data types and their sizes
// - task2() - Calculates and prints the last positive value for short and unsigned short
// - task3() - Prints the last positive value of short when incrementing by 10000

#include <stdio.h>
#include <limits.h>

void task1(void);
void task2(void);
void task3(void);
void task4(void);

// Function Name: main
// Author: Paulo Sousa
// Course: CST8152 Compilers
// Lab: Lab 0
// Date: May 1, 2021
// Professor: Paulo Sousa
// Purpose: Create a sequence of tasks to evaluate datatypes.

int main_Cdatatypes(void) {
	int code = 0;
	task1();
	task2();
	task3();
	task4();
	printf("End of execution\n");
	return code;
}

// Function Name: task1
// Course: CST8152 Compilers
// Lab: Lab 0
// Date: May 1, 2021
// Professor: Paulo Sousa
// Purpose: Prints a list of data types and their sizes

void task1(void) {
	printf("* TASK 1 *************************************\n");
	printf("The size of type char is: %d\n", (int)sizeof(char));
	printf("The size of type short int is: %d\n", (int)sizeof(short));
	printf("The size of type int is: %d\n", (int)sizeof(int));
	printf("The size of type long int is: %d\n", (int)sizeof(long));
	printf("The size of type float is: %d\n", (int)sizeof(float));
	printf("The size of type double is: %d\n", (int)sizeof(double));
	printf("The size of type long double is: %d\n", (int)sizeof(long double));
	printf("The size of type unsigned char is: %d\n", (int)sizeof(unsigned char));
	printf("The size of type unsigned short int is: %d\n", (int)sizeof(unsigned short));
	printf("The size of type unsigned int is: %d\n", (int)sizeof(unsigned int));
	printf("The size of type unsigned long int is: %d\n", (int)sizeof(unsigned long));
	printf("The size of derived type size_t is: %d\n", (int)sizeof(size_t));
	printf("The size of derived type wchar_t is: %d\n", (int)sizeof(wchar_t));
	return;
}

// Function Name: task2
// Course: CST8152 Compilers
// Lab: Lab 0
// Date: May 1, 2021
// Professor: Paulo Sousa
// Purpose: Calculates and prints the last positive value for short and unsigned short

void task2(void) {
	printf("* TASK 2 *************************************\n");
	// Signed values
	int max_value = 1;
	int i;
	for (i = 0; i < sizeof(short) * 8 - 1; i++) {
		max_value *= 2;
	}
	max_value -= 1;
	printf("The last positive value is: %d\n", max_value);
	printf("SHRT_MAX = %d\n", SHRT_MAX);
	// Unsigned values
	max_value = 1;
	for (i = 0; i < sizeof(short) * 8; i++) {
		max_value *= 2;
	}
	max_value -= 1;
	printf("The last positive unsigned value is: %u\n", max_value);
	printf("USHRT_MAX = %d\n", USHRT_MAX);
	return;
}

// Function Name: task3
// Course: CST8152 Compilers
// Lab: Lab 0
// Date: May 1, 2021
// Professor: Paulo Sousa
// Purpose: Prints the last positive value of short when incrementing by 100

void task3(void) {
	printf("* TASK 3 *************************************\n");
	char val = 0;
	char inc = 100;
	while (val>= 0) {
		printf("val: %d\n", val);
		val += inc;
	}
	val -= inc;
	printf("The last positive value is: %d\n", val);
	return;
}

// Function Name: task3
// Course: CST8152 Compilers
// Lab: Lab 0
// Date: May 1, 2021
// Professor: Paulo Sousa
// Purpose: Prints the last positive value of short when incrementing by 100

void task4(void) {
	printf("* TASK 4 *************************************\n");
	unsigned char val = 0, val0 = 0;
	char inc = 100;
	while (val >= val0) {
		printf("val: %d\n", val);
		val0 = val;
		val += inc;
	}
	printf("The last positive value is: %d\n", val0);
	return;
}
