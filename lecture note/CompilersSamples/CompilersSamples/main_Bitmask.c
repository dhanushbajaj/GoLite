// File name: bitmask.c
// This program illustrates how to use masks and bitwise operation to change a specific bit
// or several bits without affecting the rest of the bits in a data field.
// It shows how to work with 2-bits fields and 1-bit (LSB - bit 0) field.
// Similar 1-bit masks and operations should be used in Buffer implementation
// Author: Svillen Ranev.

#include <stdio.h>

 // MASKS
 // 16 bit field  MSB-> 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0 <-LSB
#define DEFAULTZ    0x0000   // 0000 0000 0000 0000
#define DEFAULT     0xEA57   // 1110 1010 0101 0111
#define RESET1413   0x9FFF   // 1001 1111 1111 1111
#define SET1413_01  0x2000   // 0010 0000 0000 0000
#define SET1413_10  0x4000   // 0100 0000 0000 0000
#define SET_LSB     0x0001   // 0000 0000 0000 0001
#define RESET_LSB   0xFFFE   // 1111 1111 1111 1110
#define CHK_LSB     0x0001   // 0000 0000 0000 0001

int main_Bitmask(void) {

	// data bit field
	unsigned short bit_field = 0;

    // Print the number of bits in bit_field
	printf("Number of bits in bit_field: %d\n", (int)(sizeof(bit_field) * 8));

	// Uses the NOT operator
	printf("Initialization\n");
	bit_field = DEFAULTZ;
	printf("The contents of bit_field in hex: %4X\n", bit_field);
	bit_field = ~bit_field;
	printf("Inverts the default value \n");
	printf("The contents of bit_field in hex: %4X\n", bit_field);
	bit_field = ~bit_field;
	printf("Second inversion \n");
	printf("The contents of bit_field in hex: %4X\n", bit_field);

	// set bit_field to 0 using bitwise AND(&)
	bit_field = bit_field & DEFAULTZ;
	printf("Set all bits to zero\n");
	printf("The contents of bit_field in hex: %4X\n", bit_field);

	// Set the default value of bit_field using bitwise OR (|)
	// Bitwise OR (|) is used because all bits in bit_field was set to 0
	// Bitwise AND can be used as well but all bits must be set to 1 first
	bit_field = bit_field | DEFAULT;
	printf("Set all bits to default - 0xEA57 -> 1110 1010 0101 0111\n");
	printf("The contents of bit_field in hex: %X\n", bit_field);

	// Set bit 14 and 13 to 01. Do not change any other bit.
	// First reset, then set
	bit_field &= RESET1413;
	printf("Reset bits 14 and 13 - set them to zero\n");
	printf("The contents of bit_field in hex: %X\n", bit_field);
	printf("Set bits 14 and 13 to 0 1\n");
	bit_field |= SET1413_01;
	printf("The contents of bit_field in hex: %X\n", bit_field);

	// Set bit 14 and 13 to 10. First reset, then set
	bit_field &= RESET1413;
	printf("Reset bits 14 and 13 - set them to zero\n");
	printf("The contents of bit_field in hex: %X\n", bit_field);
	bit_field |= SET1413_10;
	printf("Set bits 14 and 13 to 1 0\n");
	printf("The contents of bit_field in hex: %X\n", bit_field);

	// Check the LSB (bit0). If 1, reset to 0. Do not change any other bits
	printf("The value of bit_field determined only by the LSB(bit0) in hex: %X\n", bit_field & CHK_LSB);
	if ((bit_field & CHK_LSB) == 1) {
		printf("Reset LSB to 0\n");
		bit_field = bit_field & RESET_LSB;
	}
	printf("The contents of bit_field in hex: %X\n", bit_field);
	printf("The value of bit_field determined only by the LSB(bit0) in hex: %X\n", bit_field & CHK_LSB);

	// Set the LSB (bit0) to 0. Do not change any other bits
	printf("Set LSB to 1 again\n");
	bit_field = bit_field | SET_LSB;
	printf("The contents of bit_field in hex: %X\n", bit_field);
	printf("The value of bit_field determined only by the LSB(bit0): %X\n", bit_field & CHK_LSB);
	return 0;
}
