/*
    Donovan Ellison
    11-29-2018

    present.h - Header for PRESENT-80 functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Length of the input block for the cipher
#define BLOCK_LENGTH 8

// XOR the round key with the state
void add_round_key(unsigned char *, unsigned char *);

// Process the state through the s box
void s_box_layer(unsigned char *);

// Bit permutation of the state
void p_layer(unsigned char *);

// Update the key given the current key and round counter
void generate_round_key(unsigned char *, int);

// Encrypt a 64-bit block using a 80-bit key
void encryption(unsigned char *, unsigned char *);

// Convert an unsigned char array to binary string
void str_to_bin(unsigned char *, char *, int);

// Convert a binary string to an unsigned char array
void bin_to_str(unsigned char *, char *, int);

// Convert a hexedecimal number to binary
char* hex_to_bin(char);

// Reverse a char array of a given length
void reverse(char *, int);

// Rotate a char array of a given lnegth a specified amount
void rotate(char *, int, int);
