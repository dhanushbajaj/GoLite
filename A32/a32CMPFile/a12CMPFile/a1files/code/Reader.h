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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152   Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

 /* TIP: Do not change pragmas, unless necessary .......................................*/
 /*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
 /*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

 /* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR		(-1)						/* General error message */
#define READER_TERMINATOR	'\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (GoLite) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */
/* TO_DO: BIT 3: END = End of buffer flag */
#define READER_FLAG_END     0x08    /* (0000 1000)_2 = (008)_16 */

/* TO_DO: BIT 2: REL = Rellocation memory flag */
#define READER_FLAG_REL     0x04    /* (0000 0100)_2 = (004)_16 */

/* TO_DO: BIT 1: EMP = Buffer empty flag */
#define READER_FLAG_EMP     0x02    /* (0000 0010)_2 = (002)_16 */

/* TO_DO: BIT 0: FUL = Buffer full flag */
#define READER_FLAG_FUL     0x01    /* (0000 0001)_2 = (001)_16 */


#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (GoLite) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	GoLite_intg mark;			/* the offset to the mark position (in chars) */
	GoLite_intg read;			/* the offset to the get a char position (in chars) */
	GoLite_intg wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	GoLite_string	content;			/* pointer to the beginning of character array (character buffer) */
	GoLite_intg		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	GoLite_intg		increment;			/* character array increment factor */
	GoLite_intg		mode;				/* operational mode indicator */
	GoLite_byte		flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		position;				/* Offset / position field */
	GoLite_intg		histogram[NCHAR];	/* Statistics of chars */
	GoLite_intg		numReaderErrors;	/* Number of errors from Reader */
} Buffer, * BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
BufferPointer	readerCreate(GoLite_intg, GoLite_intg, GoLite_intg);
BufferPointer	readerAddChar(BufferPointer const, rune);
GoLite_boln		readerClear(BufferPointer const);
GoLite_boln		readerFree(BufferPointer const);
GoLite_boln		readerIsFull(BufferPointer const);
GoLite_boln		readerIsEmpty(BufferPointer const);
GoLite_boln		readerSetMark(BufferPointer const, GoLite_intg);
GoLite_intg		readerPrint(BufferPointer const);
GoLite_intg		readerLoad(BufferPointer const, FILE* const);
GoLite_boln		readerRecover(BufferPointer const);
GoLite_boln		readerRetract(BufferPointer const);
GoLite_boln		readerRestore(BufferPointer const);
/* Getters */
rune	readerGetChar(BufferPointer const);
GoLite_string	readerGetContent(BufferPointer const, GoLite_intg);
GoLite_intg		readerGetPosRead(BufferPointer const);
GoLite_intg		readerGetPosWrte(BufferPointer const);
GoLite_intg		readerGetPosMark(BufferPointer const);
GoLite_intg		readerGetSize(BufferPointer const);
GoLite_intg		readerGetInc(BufferPointer const);
GoLite_intg		readerGetMode(BufferPointer const);
GoLite_byte		readerGetFlags(BufferPointer const);
GoLite_void		readerPrintStat(BufferPointer const);
GoLite_intg		readerNumErrors(BufferPointer const);

#endif
