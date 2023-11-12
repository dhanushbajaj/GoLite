#include <stdio.h>
#include <limits.h>  // for INT_MAX, INT_MIN
#include <stdlib.h>  // strtol
#include "main.h"

/* Main code - to test examples used in Labs for demo (Professor) */
int main(int argc, char** argv) {
	int ret = 0;
	int option = DEFAULT_OPTION;
	// Printing parameters
	printf("Parameters:\n");
	printf("argc = %d\n", argc);
	for (int i = 0; i < argc; ++i)
		printf("argv[%d] = %s\n", i, argv[i]);
	// Convert parameter
	if (argc > 1) {
		option = atoi(argv[1]);
	}
	// Switch labs
	printf("COMPILERS EXAMPLES *******************************\n");
	switch (option) {
	// Basic labs .................................................
	case LAB1:
		printf("Lab 1 - Datatypes ****************************\n");
		ret = ret + main_Cdatatypes();
		break;
	case LAB2:
		printf("Lab 2 - Asciitest ****************************\n");
		ret = ret + main_AscTable();
		break;
	case LAB3:
		printf("Lab 3 - Bitmasks *****************************\n");
		ret = ret + main_Bitmask();
		break;
	case LAB4:
		printf("Lab 4 - Enumerations *************************\n");
		ret = ret + main_Enumerations();
		break;
	case LAB5:
		printf("Lab 5 - Pointers *****************************\n");
		ret = ret + main_PointerDatatypes();
		break;
	case LAB6:
		printf("Lab 6 - Function pointers 1 ******************\n");
		ret = ret + main_BasicFunctionPointers();
		break;
	case LAB7:
		printf("Lab 7 - Function pointers 2 ******************\n");
		ret = ret + main_FunctionPointers();
		break;
	case LAB8:
		printf("Lab 8 - Lambda boolean ***********************\n");
		ret = ret + main_BooleanFunctions();
		break;
	case LAB9:
		printf("Lab 9 - TM ***********************************\n");
		ret = ret + main_TuringMachine();
		break;

	// Error .................................................
	default:
		printf("%s%d%s%d%s", "* ERROR: Option required from ", LAB1, " to ", LAB9, "...\n");
		break;
	}
	return ret;
}
