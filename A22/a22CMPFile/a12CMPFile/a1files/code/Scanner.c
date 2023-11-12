/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2023
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************
=---------------------------------------=
|  COMPILERS - ALGONQUIN COLLEGE (F23)  |
=---------------------------------------=
|              ....                     |
|          ........::.::::::.           |
|        .:........::.:^^^~~~:          |
|        :^^::::::^^^::^!7??7~^.        |
|       .:^~~^!77777~~7?YY?7??7^.       |
|       :.^~!??!^::::^^~!?5PY??!~.      |
|       ~!!7J~.:::^^^^~!!~~?G5J?~       |
|       :^~?!~7?Y57^^?PP5YJ!J5Y?:       |
|       .~!!.:^!7!:.:7JYYJ7~7Y7^        |
|       .~77..    . .~^:^^^~7?:         |
|       .^!^~:::.:^!7?~^~!77J:          |
|        ^^!Y~^^^^~?YJ77??7JJ^          |
|       .^7J?~^~~^~7??7??7JY?~:         |
|        ::^^~^7?!^~~!7???J?J7~:.       |
|         ^~~!.^7YPPPP5Y?7J7777~.       |
|        ..:~..:^!JPP5YJ?!777!^.        |
| .~?JJJJJJJJJJYYYYYPPPPPPPPPPPP5PPYY~  |
|  :!Y5GGG.___ YYYYYY__._.PPGGGGGG5!.   |
|   :!Y5G / __| ___ / _(_)__ _ PGP5.    |
|    :~75 \__ \/ _ \  _| / _` | 5?.     |
|     7~7 |___/\___/_| |_\__,_| Y5?.    |
|    .^~!~.....................P5YY7.   |
|   .:::::::::::::?JJJJYYYYYYYYYJJJJ7.  |
|                                       |
=---------------------------------------=
*/

/*
************************************************************
* File name: Scanner.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2022
* Purpose: This file contains all functionalities from Scanner.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

 /* The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
  * to suppress the warnings about using "unsafe" functions like fopen()
  * and standard sting library functions defined in string.h.
  * The define does not have any effect in Borland compiler projects.
  */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>   /* standard input / output */
#include <ctype.h>   /* conversion functions */
#include <stdlib.h>  /* standard library functions and constants */
#include <string.h>  /* string functions */
#include <limits.h>  /* integer types constants */
#include <float.h>   /* floating-point types constants */

/* #define NDEBUG to suppress assert() call */
#include <assert.h>  /* assert() prototype */

/* project header files */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/*
----------------------------------------------------------------
TO_DO: Global vars definitions
----------------------------------------------------------------
*/

/* Global objects - variables */
/* This buffer is used as a repository for string literals. */
extern BufferPointer stringLiteralTable;	/* String literal table */
GoLite_intg line = 1;                      /* Current line number of the source code */
extern GoLite_intg errorNumber;				/* Defined in platy_st.c - run-time error number */

extern GoLite_intg stateType[NUM_STATES];
extern GoLite_string keywordTable[KWT_SIZE];
extern PTR_ACCFUN finalStateTable[NUM_STATES];
extern GoLite_intg transitionTable[NUM_STATES][CHAR_CLASSES];

/* Local(file) global objects - variables */
static BufferPointer lexemeBuffer;			/* Pointer to temporary lexeme buffer */
static BufferPointer sourceBuffer;			/* Pointer to input source buffer */

/*
 ************************************************************
 * Intitializes scanner
 *		This function initializes the scanner using defensive programming.
 ***********************************************************
 */
 /* TO_DO: Follow the standard and adjust datatypes */

GoLite_intg startScanner(BufferPointer psc_buf) {
	// Initialize the line number
	line = 1;

	// Check if the buffer is not NULL
	if (psc_buf == NULL) {
		fprintf(stderr, "Scanner Error: Null buffer passed to startScanner\n");
		return EXIT_FAILURE;
	}

	// Set up the source buffer for the scanner
	sourceBuffer = psc_buf;

	/* TO_DO: Start histogram */
	for (GoLite_intg i=0; i<NUM_TOKENS;i++)
		scData.scanHistogram[i] = 0;
	/* Basic scanner initialization */
	/* in case the buffer has been read previously  */
	readerRecover(psc_buf);
	readerClear(stringLiteralTable);
	line = 1;
	sourceBuffer = psc_buf;
	return EXIT_SUCCESS; /*0*/
}

/*
 ************************************************************
 * Process Token
 *		Main function of buffer, responsible to classify a char (or sequence
 *		of chars). In the first part, a specific sequence is detected (reading
 *		from buffer). In the second part, a pattern (defined by Regular Expression)
 *		is recognized and the appropriate function is called (related to final states 
 *		in the Transition Diagram).
 ***********************************************************
 */

Token tokenizer(GoLite_void) {

	/* TO_DO: Follow the standard and adjust datatypes */

	Token currentToken = { 0 }; /* token to return after pattern recognition. Set all structure members to 0 */
	rune c;	/* input symbol */
	GoLite_intg state = 0;		/* initial state of the FSM */
	GoLite_intg lexStart;		/* start offset of a lexeme in the input char buffer (array) */
	GoLite_intg lexEnd;		/* end offset of a lexeme in the input char buffer (array)*/

	GoLite_intg lexLength;		/* token length */
	GoLite_intg i;				/* counter */
	/*
	rune newc;			// new char
	*/

	while (1) { /* endless loop broken by token returns it will generate a warning */
		c = readerGetChar(sourceBuffer);

		/* ------------------------------------------------------------------------
			Part 1: Implementation of token driven scanner.
			Every token is possessed by its own dedicated code
			-----------------------------------------------------------------------
		*/

		/* TO_DO: All patterns that do not require accepting functions */
		switch (c) {

		/* Cases for spaces */
		case ' ':
		case '\t':
		case '\f':
			break;
		case '\n':
			line++;
			break;

		/* Cases for symbols */
		case ';':
			currentToken.code = EOS_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '(':
			currentToken.code = LPR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case ')':
			currentToken.code = RPR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '{':
			currentToken.code = LBR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '}':
			currentToken.code = RBR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		/* Cases for END OF FILE */
		case CHARSEOF0:
			currentToken.code = SEOF_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.seofType = SEOF_0;
			return currentToken;
		case CHARSEOF255:
			currentToken.code = SEOF_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.seofType = SEOF_255;
			return currentToken;

		/* ------------------------------------------------------------------------
			Part 2: Implementation of Finite State Machine (DFA) or Transition Table driven Scanner
			Note: Part 2 must follow Part 1 to catch the illegal symbols
			-----------------------------------------------------------------------
		*/

		/* TO_DO: Adjust / check the logic for your language */

		default: // general case
			state = nextState(state, c);
			lexStart = readerGetPosRead(sourceBuffer) - 1;
			readerSetMark(sourceBuffer, lexStart);
			int pos = 0;
			while (stateType[state] == NOFS) {
				c = readerGetChar(sourceBuffer);
				state = nextState(state, c);
				pos++;
			}
			if (stateType[state] == FSWR)
				readerRetract(sourceBuffer);
			lexEnd = readerGetPosRead(sourceBuffer);
			lexLength = lexEnd - lexStart;
			lexemeBuffer = readerCreate((GoLite_intg)lexLength + 2, 0, MODE_FIXED);
			if (!lexemeBuffer) {
				fprintf(stderr, "Scanner error: Can not create buffer\n");
				exit(1);
			}
			readerRestore(sourceBuffer);
			for (i = 0; i < lexLength; i++)
				readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
			readerAddChar(lexemeBuffer, READER_TERMINATOR);
			currentToken = (*finalStateTable[state])(readerGetContent(lexemeBuffer, 0));
			readerRestore(lexemeBuffer); //xxx
			return currentToken;
		} // switch

	} //while

} // tokenizer


/*
 ************************************************************
 * Get Next State
	The assert(int test) macro can be used to add run-time diagnostic to programs
	and to "defend" from producing unexpected results.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	(*) assert() is a macro that expands to an if statement;
	if test evaluates to false (zero) , assert aborts the program
	(by calling abort()) and sends the following message on stderr:
	(*) Assertion failed: test, file filename, line linenum.
	The filename and linenum listed in the message are the source file name
	and line number where the assert macro appears.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	If you place the #define NDEBUG directive ("no debugging")
	in the source code before the #include <assert.h> directive,
	the effect is to comment out the assert statement.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	The other way to include diagnostics in a program is to use
	conditional preprocessing as shown bellow. It allows the programmer
	to send more details describing the run-time problem.
	Once the program is tested thoroughly #define DEBUG is commented out
	or #undef DEBUG is used - see the top of the file.
 ***********************************************************
 */
 /* TO_DO: Just change the datatypes */

GoLite_intg nextState(GoLite_intg state, rune c) {
	GoLite_intg col;
	GoLite_intg next;
	col = nextClass(c);
	next = transitionTable[state][col];
	if (DEBUG)
		printf("Input symbol: %c Row: %d Column: %d Next: %d \n", c, state, col, next);
	assert(next != FS);
	if (DEBUG)
		if (next == FS) {
			printf("Scanner Error: Illegal state:\n");
			printf("Input symbol: %c Row: %d Column: %d\n", c, state, col);
			exit(1);
		}
	return next;
}

/*
 ************************************************************
 * Get Next Token Class
	* Create a function to return the column number in the transition table:
	* Considering an input char c, you can identify the "class".
	* For instance, a letter should return the column for letters, etc.
 ***********************************************************
 */
/* TO_DO: Use your column configuration */

/* Adjust the logic to return next column in TT */
/*    [A-z],[0-9],    _,    &,   \', SEOF,    #, other
	   L(0), D(1), U(2), M(3), Q(4), E(5), C(6),  O(7) */

	   /*
		* Determines the class of a character for the transition table.
		* This function returns the column number in the transition table
		* based on the input character 'c'.
		*/
		/*
		 * Determines the class of a character for the transition table.
		 */
	GoLite_intg nextClass(rune c) {
		if (isalpha(c)) return 0;  // L (Letters)
		if (isdigit(c)) return 1;  // D (Digits)
		if (c == CHRCOL2) return 2;  // U (Underscore)
		if (c == CHRCOL3) return 3;  // Q (Double Quotation Marks)
		if (c == CHRCOL4) return 4;  // q (Single Quotation Marks)
		if (c == CHRCOL5) return 5;  // E (Exclamation Mark)
		if (c == CHRCOL6) return 6;  // B (Forward Slash)
		if (c == CHRCOL7) return 7;  // S (Star)

	// Handling EOF characters
	if (c == CHRCOL8 || c == CHARSEOF255) return 8;

	// Default case for other characters
	return 9;
}


/*
 ************************************************************
 * Acceptance State Function COM
 *		Function responsible to identify COM (comments).
 ***********************************************************
 */
 /* TO_DO: Adjust the function for IL */

Token funcCMT(GoLite_string lexeme) {
	Token currentToken = { 0 };
	currentToken.code = CMT_T; // Set the token code to comment type

	// Counting the number of lines in the comment
	GoLite_intg len = (GoLite_intg)strlen(lexeme);
	for (GoLite_intg i = 0; i < len; i++) {
		if (lexeme[i] == '\n') {
			line++;
		}
	}

	// Updating the histogram for the comment token
	scData.scanHistogram[currentToken.code]++;

	return currentToken;
}


 /*
  ************************************************************
  * Acceptance State Function IL
  *		Function responsible to identify IL (integer literals).
  * - It is necessary respect the limit (ex: 2-byte integer in C).
  * - In the case of larger lexemes, error shoul be returned.
  * - Only first ERR_LEN characters are accepted and eventually,
  *   additional three dots (...) should be put in the output.
  ***********************************************************
  */
  /* TO_DO: Adjust the function for IL */

Token funcIL(GoLite_string lexeme) {
	Token currentToken = { 0 };
	GoLite_long tlong;

	// Check if the lexeme exceeds the maximum length for integer literals
	if (lexeme[0] != '\0' && strlen(lexeme) > NUM_LEN) {
		// Handle error for lexemes that are too long
		currentToken = (*finalStateTable[ESNR])(lexeme); // Error state function
	}
	else {
		// Convert the lexeme to a long integer
		tlong = atol(lexeme);

		// Check if the converted value is within the range of an integer
		if (tlong >= INT_MIN && tlong <= INT_MAX) {
			currentToken.code = INL_T; // Set token code to integer literal
			currentToken.attribute.intValue = (GoLite_intg)tlong; // Set attribute value
		}
		else {
			// Handle error for out-of-range values
			currentToken = (*finalStateTable[ESNR])(lexeme); // Error state function
		}
	}

	// Update the histogram for the integer literal token
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}


/*
 ************************************************************
 * Acceptance State Function ID
 *		In this function, the pattern for IDs must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for ID */

Token funcID(GoLite_string lexeme) {
	Token currentToken = { 0 };
	size_t length = strlen(lexeme);

	// Assuming GoLite has specific suffixes to identify method names
	// Check if the lexeme is a method name identifier
	if (length > 0 && lexeme[length - 1] == MNID_SUF) {
		currentToken.code = MNID_T; // Token code for method name identifier
		lexeme[length - 1] = '\0'; // Remove the suffix for proper lexeme storage
	}
	else {
		// Check if the lexeme is a keyword
		currentToken = funcKEY(lexeme);
		if (currentToken.code == KW_T) {
			return currentToken; // Return if it's a keyword
		}

		// If not a keyword, it's a variable identifier
		currentToken.code = VID_T; // Token code for variable identifier
	}

	// Copy the lexeme to the token's attribute, respecting the limit
	strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
	currentToken.attribute.idLexeme[VID_LEN] = '\0'; // Ensure null-termination

	// Update histogram
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}

/*
************************************************************
 * Acceptance State Function SL
 *		Function responsible to identify SL (string literals).
 * - The lexeme must be stored in the String Literal Table 
 *   (stringLiteralTable). You need to include the literals in 
 *   this structure, using offsets. Remember to include \0 to
 *   separate the lexemes. Remember also to incremente the line.
 ***********************************************************
 */
/* TO_DO: Adjust the function for SL */

Token funcSL(GoLite_string lexeme) {
	Token currentToken = { 0 };
	currentToken.code = STR_T; // Set token code to string literal

	// Store the offset of the string in the string literal table
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);

	// Process the lexeme to store it in the string literal table
	GoLite_intg len = (GoLite_intg)strlen(lexeme);
	for (GoLite_intg i = 1; i < len - 1; i++) { // Exclude the quotation marks
		if (lexeme[i] == '\n') {
			line++; // Increment line counter for new lines
		}

		// Add character to string literal table and handle buffer overflow
		if (!readerAddChar(stringLiteralTable, lexeme[i])) {
			// Handle error in case of buffer overflow
			currentToken.code = RTE_T;
			scData.scanHistogram[currentToken.code]++;
			strcpy(currentToken.attribute.errLexeme, "Run Time Error: String Literal too long");
			errorNumber = RTE_CODE;
			return currentToken;
		}
	}

	// Add a null terminator to the end of the string in the table
	if (!readerAddChar(stringLiteralTable, CHARSEOF0)) {
		// Handle error in case of buffer overflow
		currentToken.code = RTE_T;
		scData.scanHistogram[currentToken.code]++;
		strcpy(currentToken.attribute.errLexeme, "Run Time Error: String Literal too long");
		errorNumber = RTE_CODE;
		return currentToken;
	}

	// Update the histogram for the string literal token
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}


/*
************************************************************
 * This function checks if one specific lexeme is a keyword.
 * - Tip: Remember to use the keywordTable to check the keywords.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Keywords */

Token funcKEY(GoLite_string lexeme) {
	Token currentToken = { 0 };
	GoLite_intg kwindex = -1;

	// Iterate over the keyword table to find a match
	for (GoLite_intg j = 0; j < KWT_SIZE; j++) {
		if (strcmp(lexeme, keywordTable[j]) == 0) {
			kwindex = j; // Keyword found
			break;
		}
	}

	if (kwindex != -1) {
		// If a keyword is found, set appropriate token attributes
		currentToken.code = KW_T; // Set token code to keyword
		currentToken.attribute.codeType = kwindex; // Set keyword index
	}
	else {
		// If not a keyword, handle it as an error or as an identifier
		// Depending on your language specification, you may want to return 
		// an identifier token or handle it as an error
		currentToken = funcErr(lexeme);
	}

	// Update the histogram for the keyword token
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}


/*
************************************************************
 * Acceptance State Function Error
 *		Function responsible to deal with ERR token.
 * - This function uses the errLexeme, respecting the limit given
 *   by ERR_LEN. If necessary, use three dots (...) to use the
 *   limit defined. The error lexeme contains line terminators,
 *   so remember to increment line.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Errors */

Token funcErr(GoLite_string lexeme) {
	Token currentToken = { 0 };
	GoLite_intg len = (GoLite_intg)strlen(lexeme);

	// Truncate the lexeme if it's longer than ERR_LEN and append "..."
	if (len > ERR_LEN) {
		strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN - 3);
		currentToken.attribute.errLexeme[ERR_LEN - 3] = '\0'; // Ensure null-termination
		strcat(currentToken.attribute.errLexeme, "...");
	}
	else {
		strcpy(currentToken.attribute.errLexeme, lexeme);
	}

	// Count new lines within the error lexeme
	for (GoLite_intg i = 0; i < len; i++) {
		if (lexeme[i] == '\n') {
			line++;
		}
	}

	// Set the token code to error and update the histogram
	currentToken.code = ERR_T;
	scData.scanHistogram[currentToken.code]++;

	return currentToken;
}


/*
 ************************************************************
 * The function prints the token returned by the scanner
 ***********************************************************
 */

GoLite_void printToken(Token t) {
	extern GoLite_string keywordTable[]; /* link to keyword table in */
	switch (t.code) {
	case RTE_T:
		printf("RTE_T\t\t%s", t.attribute.errLexeme);
		/* Call here run-time error handling component */
		if (errorNumber) {
			printf("%d", errorNumber);
			exit(errorNumber);
		}
		printf("\n");
		break;
	case ERR_T:
		printf("ERR_T\t\t%s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T\t\t%d\t ", (GoLite_intg)t.attribute.codeType);
		printf("%s\n", readerGetContent(stringLiteralTable, (GoLite_intg)t.attribute.codeType));
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case KW_T:
		printf("KW_T\t\t%s\n", keywordTable[t.attribute.codeType]);
		break;
	case CMT_T:
		printf("CMT_T\n");
		break;
	case EOS_T:
		printf("EOS_T\n");
		break;
	default:
		printf("Scanner error: invalid token code: %d\n", t.code);
	}
}

/*
 ************************************************************
 * The function prints statistics of tokens
 * Param:
 *	- Scanner data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
GoLite_void printScannerData(ScannerData scData) {
	/* Print Scanner statistics */
	printf("Statistics:\n");
	printf("----------------------------------\n");
	int cont = 0;
	for (cont = 0; cont < NUM_TOKENS; cont++) {
		if (scData.scanHistogram[cont] > 0)
			printf("%s%s%s%d%s", "Token[", tokenStrTable[cont], "]=", scData.scanHistogram[cont], "\n");
	}
	printf("----------------------------------\n");
}

/*
TO_DO: (If necessary): HERE YOU WRITE YOUR ADDITIONAL FUNCTIONS (IF ANY).
*/
