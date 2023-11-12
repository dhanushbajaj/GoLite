#pragma once

#ifndef MAIN_
	#define MAIN_
#endif

// Constants
#define MY_TRUE		1
#define MY_FALSE	0
#define HELP		0			// Help
#define ERR			(-1)		// Default error
#define IS_DEBUG	MY_FALSE	// Uses debug
#define IS_RAND		MY_FALSE	// Uses random
#define IS_CONSOLE	MY_FALSE	// Uses console

#define LAB1	101	// Lab 1  - C Datatypes basic
#define LAB2	102	// Lab 2  - Ascii test (valid chars)
#define LAB3	103	// Lab 3  - Bitmask operations
#define LAB4	104	// Lab 4  - Pointer declarations
#define LAB5	105	// Lab 5  - Function pointers
#define LAB6	106	// Lab 6  - Enumerations
#define LAB7	107	// Lab 7  - More function pointers
#define LAB8	108	// Lab 8  - Boolean functions
#define LAB9	109	// Lab 9  - TM

#define DEFAULT_OPTION LAB9	// Default lab (to be changed)

// Prototypes
int main_Cdatatypes(void);				// Lab  1
int main_AscTable(void);				// Lab  2
int main_Bitmask(void);					// Lab  3
int main_Enumerations(void);			// Lab  4
int main_PointerDatatypes(void);		// Lab  5
int main_BasicFunctionPointers(void);	// Lab  6
int main_FunctionPointers(void);		// Lab  7
int main_BooleanFunctions(void);		// Lab  8
int main_TuringMachine(void);			// Lab  9
