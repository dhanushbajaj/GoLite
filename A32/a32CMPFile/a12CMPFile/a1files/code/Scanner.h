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
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152   Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_


#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20   /* Variable identifier length */
#define ERR_LEN 40   /* Error message length */
#define NUM_LEN 5    /* Maximum number of digits for IL */

#define RTE_CODE 1   /* Value for run-time error */

/* Define the number of tokens */
#define NUM_TOKENS 13

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,    /* Error token */
	SEOF_T,   /* Source end-of-file token */
	INL_T,    /* Integer literal token */
	FPL_T,    /* Floating point literal token */
	STR_T,    /* String literal token */
	MNID_T,   /* Method name identifier token */
	VID_T,    /* Variable identifier token */
	KW_T,     /* Keyword token */
	KW_data,
	KW_code,
	LPR_T,    /* Left parenthesis token */
	RPR_T,    /* Right parenthesis token */
	LBR_T,    /* Left brace token */
	RBR_T,    /* Right brace token */
	EOS_T,    /* End of statement (semicolon) */
	CMT_T,    /* Comment token */
	RTE_T,    /* Runtime error token */
	IVID_T,   /* Integer variable identifier token */
	FVID_T,   /* Floating-point variable identifier token */
	SVID_T,   /* String variable identifier token */
	COM_T     /* Comma token */
};


/* TO_DO: Define the list of keywords */
static const char* keywordStrTable[] = {
	"if", "else", "while", "for", "return",
	"break", "continue", "func", "var", "true",
	"false", "int", "float", "string"
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	GoLite_intg codeType;             /* Integer attributes accessor */
	AriOperator arithmeticOperator;  /* Arithmetic operator attribute code */
	RelOperator relationalOperator;  /* Relational operator attribute code */
	LogOperator logicalOperator;     /* Logical operator attribute code */
	GoLite_intg intValue;             /* Integer literal attribute (value) */
	GoLite_real floatValue;           /* Floating-point literal attribute (value) */
	GoLite_intg keywordIndex;         /* Keyword index in the keyword table */
	rune idLexeme[VID_LEN + 1];/* Variable identifier token attribute */
	rune errLexeme[ERR_LEN + 1];/* Error token attribute */
	GoLite_intg contentString;        /* String literal offset from the string literal buffer */
	EofOperator seofType;             /* Source end-of-file type */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	GoLite_byte flags;               /* Flags information */
	union {
		GoLite_intg intValue;        /* Integer value */
		GoLite_real floatValue;      /* Float value */
		GoLite_string stringContent; /* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	GoLite_intg code;               /* Token code */
	TokenAttribute attribute;      /* Token attribute */
	IdAttibutes idAttribute;       /* Not used in this scanner implementation */
} Token;

/* Scanner */
typedef struct scannerData {
	GoLite_intg scanHistogram[NUM_TOKENS];  /* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */

 /* TO_DO: Define lexeme FIXED classes */
 /* These constants will be used on nextClass */
#define CHRCOL_L 'L'   // Letters [A-Z | a-z]
#define CHRCOL_D 'D'  // Digits [0-9]
#define CHRCOL_U '_'  // Underscore [_]
#define CHRCOL_Q '"'   // Double Quotation Marks ["]
#define CHRCOL_q '\''  // Single Quotation Marks [']
#define CHRCOL_E '!'   // Exclamation Mark [!]
#define CHRCOL_B '/'   // Forward Slash [/]
#define CHRCOL_S '*'   // Star [*]
#define CHRCOL_O 'O'   // Other characters


/* These constants will be used on VID / MID function */
#define MNID_SUF '&'
#define COMM_SYM '#'

/* TO_DO: Error states and illegal state */
#define ESNR	8		/* Error state with no retract */
#define ESWR	9		/* Error state with retract */
#define FS		10		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		10
#define CHAR_CLASSES	8

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */
#define ES     -1  /* Error State */

static GoLite_intg transitionTable[NUM_STATES][CHAR_CLASSES] = {
	/*  [L(A-Z)],  [D(0-9)],  [U(_)],  [M(&)],  [Q(')],   [O],  Output Type,  State Type */
	/*  L(0),      D(1),      U(2),    M(3),    Q(4),     O(7) */
	{         1,         2,      ES,      ES,       4,      ES,     NOFS},  // S0
	{         1,         1,       1,      ES,      ES,      ES,     NOFS},  // S1
	{        ES,         2,      ES,      ES,      ES,       3,     FSNR},  // S2
	{        ES,         3,      ES,      ES,      ES,      ES,     FSNR},  // S3
	{         4,         4,       4,       4,       5,       4,     NOFS},  // S4
	{        ES,        ES,      ES,      ES,      ES,      ES,     FSNR},  // S5
	{        ES,        ES,      ES,       7,      ES,      ES,     NOFS},  // S6
	{         7,         7,       7,       7,       7,       8,     NOFS},  // S7
	{        ES,        ES,      ES,      ES,      ES,      ES,     FSWR},  // S8

};





/* TO_DO: Define list of acceptable states */
static GoLite_intg stateType[NUM_STATES] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 (MID) - Methods */
	FSWR, /* 03 (KEY) */
	NOFS, /* 04 */
	FSNR, /* 05 (SL) */
	NOFS, /* 06 */
	FSNR, /* 07 (COM) */
	FSNR, /* 08 (Err1 - no retract) */
	FSWR  /* 09 (Err2 - retract) */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
GoLite_intg			startScanner(BufferPointer psc_buf);
static GoLite_intg	nextClass(rune c);					/* character class function */
static GoLite_intg	nextState(GoLite_intg, rune);		/* state machine function */
GoLite_void			printScannerData(ScannerData scData);
Token				tokenizer(GoLite_void);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(GoLite_string lexeme);

/* Declare accepting states functions */
Token funcSL(GoLite_string lexeme);
Token funcIL(GoLite_string lexeme);
Token funcID(GoLite_string lexeme);
Token funcCMT(GoLite_string lexeme);
Token funcKEY(GoLite_string lexeme);
Token funcErr(GoLite_string lexeme);

/*
 * Accepting function (action) callback table (array) definition
 * If you do not want to use the typedef, the equvalent declaration is:
 */

 /* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* MNID	[02] */
	funcKEY,	/* KEY  [03] */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] */
	NULL,		/* -    [06] */
	funcCMT,	/* COM  [07] */
	funcErr,	/* ERR1 [06] */
	funcErr		/* ERR2 [07] */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 10

/* TO_DO: Define the list of keywords */
static GoLite_string keywordTable[KWT_SIZE] = {
	"data",		/* KW00 */
	"code",		/* KW01 */
	"int",		/* KW02 */
	"real",		/* KW03 */
	"string",	/* KW04 */
	"if",		/* KW05 */
	"then",		/* KW06 */
	"else",		/* KW07 */
	"while",	/* KW08 */
	"do"		/* KW09 */
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

 /* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	rune indentationCharType;
	GoLite_intg indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
GoLite_intg numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif
