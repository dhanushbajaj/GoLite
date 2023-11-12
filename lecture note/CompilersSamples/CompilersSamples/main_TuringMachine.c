
// TM based on DFB's busy beaver

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define UPBTAPE 25	// Tape size
#define NSYMB 5
#define LWBTAPE 1
#define FALSE 0
#define TRUE 1
#define ALPHASIZE 2

///#define DEBUG

// trivial single-card examples
// loops off to the right
char * tm01 = {"00000 01000 10111 11111"};
// loops off to the left
char * tm02 = {"00000 01000 10101 11101"};
// prints a single 1 and moves to the left
char * tm03 = {"00000 01000 10100 11000"};
// prints a single 1 and moves to the right
char * tm04 = {"00000 01000 10110 11000"};
// simple example of 2-state with optimal score of 4. 
char * tm05 = {"00000 01000 10112 11102 20101 21110"};
// classic 3-state BB producing a score of 6
char * tm06 = {"00000 01000 10102 11113 20111 21102 30112 31100"};
// another 3-state BB for sigma ?
char * tm07 = {"00000 01000 10112 11110 20013 21112 30103 31101"};
// permutation of tm3a which never terminates
char * tm08 = {"00000 01000 10112 11100 20111 21102 30102 31113"};
// another permutation of tm3a which terminates but has a score of only 2
char * tm09 = {"00000 01000 10102 11113 20112 21100 30111 31102"};
// classic 4-state tm producing a score of 23 in 107 moves 
char * tm10 = {"00000 01000 10112 11102 20101 21003 30110 31104 40114 41011" };

// (1 - state, 2 - symbol BB)
char* MT12 = "00000 01000 10110 11000";
// (2 - state, 2 - symbol BB)
char* MT22 = "00000 01000 10112 11102 20101 21110";
// (3 - state, 2 - symbol BB)
char* MT32 = "00000 01000 10112 11110 20013 21112 30103 31101";
// (4 - state, 2 - symbol BB)
char* MT42 = "00000 01000 10112 11112 20101 21003 30110 31104 40114 41011";
// (5 - state, 2 - symbol)
char* MT52 = "00000 01000 10112 11103 20113 21112 30114 31005 40101 41104 50110 51001";
// (6 - state, 2 - symbol)
char* MT62 = "00000 01000 10112 11004 20113 21016 30103 31101 40005 41110 50106 51012 60013 61015";

// Tape
/// char tape [UPBTAPE] = "0000000000000000000000000";
char* tape;
/// int tapelen = strlen(tape);
int tapelen = UPBTAPE - LWBTAPE - 1;
int headpos;

// print out the tape and on the line below it print out a ^ to show where head pos is for the next read/write
void printtape (void) {
    int i;
    for (i=0;i<tapelen;i++)
        printf ("%c ", tape[i] );                        
    putchar ('\n');
    for(i=0; i<headpos; i++)
        printf("  ") ; 
    putchar('^');
    putchar('\n');
}

// CARD X : ABCD[seq from 0 to ncards]
// ALPHASIZE = 2[=len(Alphabet)]
// - currchar = tape[headpos]
// - currtSymb = currchar - '0' 					(A = Read)      [=Alphabet]
// - currtProd = currtcard * ALPHASIZE + currtSymb                  [=Prod]
// - chtowrite = TM[currtProd][1]; 			        (B = Write)     [=Alphabet]
// - shift = TM[currtProd][2]; 				        (C = Dir)       [=Binary]
// - incdec = (shift == '0') ? -1 : +1;                             [0:L,1:R]
// - nextcard = TM[currtProd][3] - '0'; 		    (D = NxtStat)   [=Prod]
// - currtcard = nextcard;

// NEW CARDS:
// https://en.wikipedia.org/wiki/Busy_beaver
// (1 - state, 2 - symbol BB)
// MT12 = "00000 01000 10110 11000"
// (2 - state, 2 - symbol BB)
// MT22 = "00000 01000 10112 11102 20101 21110"
// (3 - state, 2 - symbol BB)
// MT32 = "00000 01000 10112 11110 20013 21112 30103 31101"
// (4 - state, 2 - symbol BB)
// MT42 = "00000 01000 10112 11112 20101 21003 30110 31104 40114 41011"
// (5 - state, 2 - symbol)
// MT52 = "00000 01000 10112 11103 20113 21112 30114 31005 40101 41104 50110 51001"
// (6 - state, 2 - symbol)
// MT62 = "00000 01000 10112 11004 20113 21016 30103 31101 40005 41110 50106 51012 60013 61015"

// Run TM
int runtm (char* thistm, int steps) {
    char currtchar, chtowrite, shift;
    int currtcard, currtSymb, nextcard, incdec, currtProd;
    // print out initial deck of cards
    printf ("Card: %s\n", thistm);
    currtcard = 1;
    headpos = tapelen / 2;
    printf("\nInitial tape (head position marked by ^):\n");
    printtape();
    printf("Game started\n");
    do {
        currtchar = tape[headpos];
        steps++;
        currtSymb = currtchar - '0'; // denotes whether a 0 or a 1 has just been read
        currtProd = (currtcard * ALPHASIZE + currtSymb)*(NSYMB+1);
        chtowrite = thistm[currtProd+2];
        shift = thistm[currtProd+3];
        incdec = (shift == '0') ? -1 : +1; // shift headpos left or right after next write 
        nextcard =  thistm[currtProd+4] - '0';
        tape[headpos] = chtowrite;
        printtape();
        headpos = headpos + incdec; 
        // sanity check
        if ((headpos < LWBTAPE - 1) || (headpos == UPBTAPE - 2)) {
            printf("[Error]: tape too short and/or TM may be looping\n"); 
            nextcard = 0;
        }
#ifdef DEBUG
        printf("[Debug]: char to print is %c \n", chtowrite);
        printf("[Debug]: shiftchar is %c \n", shift);
        printf("[Debug]: nextcard is %d \n", nextcard);
        printf("[Debug]: headpos is now %d \n", headpos);
#endif
        currtcard = nextcard;
    } while (nextcard != 0);
    return steps;
}

// Execution passing tm and cards
void run_tm_card(char** tm) {
    int i, score = 0, steps = 0;
    char** currentgame = (char**)tm;
    for (int i=0;i<UPBTAPE; i++)
        tape[i] = '0';
    steps = runtm((char*) currentgame, steps);
    if (steps == 0)
        printf("The TM has halted\n");
    printf("\nFinal tape config is:\n\n");
    printtape();
    if (steps != 1) {
        for (i = LWBTAPE; i <= UPBTAPE; i++)
            if (tape[i] == '1') score++;
        printf("\nsteps = %d - score = %d\n", steps, score);
    }
    return;
}

// Multiple TM examples
int main_TuringMachine () {
    // Tape allocation / initialization
    tape = (char*) malloc((UPBTAPE+1)*sizeof(char));
    if (!tape)
        return (-1);
    for (int i = 0; i < UPBTAPE; i++) {
        tape[i] = '0';
    }
    tape[UPBTAPE] = '\0';
    // TM Multiple cases
    printf("\nTM[01] ..............\n\n");
    run_tm_card((char**)tm01);
    printf("\nTM[02] ..............\n\n");
    run_tm_card((char**)tm02);
    printf("\nTM[03] ..............\n\n");
    run_tm_card((char**)tm03);
    printf("\nTM[04] ..............\n\n");
    run_tm_card((char**)tm04);
    printf("\nTM[05] ..............\n\n");
    run_tm_card((char**)tm05);
    printf("\nTM[06] ..............\n\n");
    run_tm_card((char**)tm06);
    printf("\nTM[07] ..............\n\n");
    run_tm_card((char**)tm07);
    printf("\nTM[08] ..............\n\n");
    run_tm_card((char**)tm08);
    printf("\nTM[09] ..............\n\n");
    run_tm_card((char**)tm09);
    printf("\nTM[10] ..............\n\n");
    run_tm_card((char**)tm10);
    // Busy beaver
    printf("\nMT[12] ..............\n\n");
    run_tm_card((char**)MT12);
    printf("\nMT[22] ..............\n\n");
    run_tm_card((char**)MT22);
    printf("\nMT[32] ..............\n\n");
    run_tm_card((char**)MT32);
    printf("\nMT[42] ..............\n\n");
    run_tm_card((char**)MT42);
    printf("\nM5[52] ..............\n\n");
    run_tm_card((char**)MT52);
    printf("\nM5[62] ..............\n\n");
    run_tm_card((char**)MT62);

    // Now run the appropriate BB Turing Machine
    free(tape);
    return 0;
}
