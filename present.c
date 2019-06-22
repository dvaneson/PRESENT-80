/*
 *  Donovan Ellison
 *  06-21-2019
 *
 *  present.c - Implementation for PRESENT-80 functions
 */

#define _GNU_SOURCE
#include "present.h"

const char s_box[]           = "C56B90AD3EF84712";
const char inv_s_box[]       = "5EF8C12DB463079A";
char       hex_binary[16][4] = {
   "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
   "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"
};

// XOR the current state with the round key
void add_round_key(unsigned char *state, unsigned char *key) {
   for (int i = 0; i < BLOCK_LENGTH; ++i) {
      state[i] ^= key[i];
   }
}

// Substitute each 4-bit word in the given state according to s_box
// Uses the inverse s_box if inverse is specified
void s_box_layer(unsigned char *state, bool inverse) {
   char hex[3], tmp[2];
   long unsigned int s;
   hex[2] = '\0';
   tmp[1] = '\0';

   for (int i = 0; i < BLOCK_LENGTH; ++i) {
      // Store the Hex value of the char in temp
      sprintf(hex, "%02X", state[i]);

      // Take the hex numbers and put them through the s_box
      tmp    = hex[0];
      s      = strtoul(&tmp, NULL, 16);
      hex[0] = inverse ? inv_s_box[s] : s_box[s];

      tmp    = hex[1];
      s      = strtoul(&tmp, NULL, 16);
      hex[1] = inverse ? inv_s_box[s] : s_box[s];

      // Convert the new hex number back to char and update state
      state[i] = (unsigned char)(strtoul(hex, NULL, 16));
   }
}

// Permute the current state such that the bit at position i goes to position
// P(i) given the rule:
//      P(i) = i * x mod 63, if 0 <= i < 63
//           = 63,            if i == 63
// Where x = 16 for the regular permutation and x=4 for the inverse permutation
void p_layer(unsigned char *state, bool inverse) {
   char prev[65], new[65];
   int  p_i;
   int  x = inverse ? 4 : 16;

   str_to_bin(state, prev, 8);
   for (int i = 0; i < 63; ++i) {
      p_i      = (i * x) % 63;
      new[p_i] = prev[i];
   }
   new[63] = prev[63];
   bin_to_str(state, new, 8);
}

// Update the key register by rotating, substituting, and XORing the key.
// Uses the round counter for the XOR, but does nothing for round 0
void generate_round_key(unsigned char *key, int counter) {
   if (counter == 0) {
      return;
   }

   char bin[81], tmp[5];
   long unsigned int s;

   // Rotate the key left 61 bits
   str_to_bin(key, bin, 10);
   rotate(bin, 80, -61);

   // Pass the first 4 bits through the s_box by first converting it to hex
   strncpy(tmp, bin, 4);
   tmp[4] = '\0';
   s      = strtoul(tmp, NULL, 2);
   hex_to_bin(s_box[s], bin);

   // Xor bits 60 to 64 with the counter
   for (int i = 0; i < 5; ++i) {
      char bit   = (counter & (1 << i)) ? '1' : '0';
      int  index = 59 + (5 - i);
      bin[index] = (bin[index] == bit) ? '0' : '1';
   }

   bin_to_str(key, bin, 10);
}

// Encrypt a 64-bit block using an 80-bit key for 31 rounds by adding the key,
// substituting the state, then permuting the state.
void encryption(unsigned char *state, unsigned char *key) {
   unsigned char round_key[32][8], key_register[10];

   // Generate the round keys and store them in the key register
   memcpy(key_register, key, 10);
   for (int i = 0; i < 32; ++i) {
      generate_round_key(key_register, i);
      memcpy(round_key[i], key_register, 8);
   }

   // Encrypt the state
   for (int i = 0; i < 31; ++i) {
      add_round_key(state, round_key[i]);
      s_box_layer(state, false);
      p_layer(state, false);
   }
   add_round_key(state, round_key[31]);
}

// Decrypt a 64-bit block using an 80-bit key for 31 rounds by adding the key,
// permuting the state, then substituting the state.
void decryption(unsigned char *state, unsigned char *key) {
   unsigned char round_key[32][8], key_register[10];

   // Generate the round keys and store them in the key register
   memcpy(key_register, key, 10);
   for (int i = 0; i < 32; ++i) {
      generate_round_key(key_register, i);
      memcpy(round_key[i], key_register, 8);
   }

   // Decrypt the state
   for (int i = 31; i > 0; --i) {
      add_round_key(state, round_key[i]);
      p_layer(state, true);
      s_box_layer(state, true);
   }
   add_round_key(state, round_key[0]);
}

// --------------------- UTILITY FUNCTIONS ----------------------


// Convert unsigned char array 'str' to a binary string and store it in 'bin'.
// Must specify length of str.
// Does not append NULL at end of the string
void str_to_bin(unsigned char *str, char *bin, int len) {
   for (int i = 0; i < len; ++i) {
      for (int j = 0; j < 8; ++j) {
         bin[i * 8 + j] = (str[i] & (1 << (7 - j))) ? '1' : '0';
      }
   }
}

// Convert binary string 'bin' to the corresponding ASCII and store it in 'str'
// Must specify length of str.
// Does not append NULL at end of the binary string
void bin_to_str(unsigned char *str, char *bin, int len) {
   char tmp[BLOCK_LENGTH + 1];

   for (int i = 0; i < len; ++i) {
      strncpy(tmp, &bin[i * BLOCK_LENGTH], BLOCK_LENGTH);
      str[i] = (unsigned char)(strtoul(tmp, NULL, 2));
   }
}

// Convert a hexadecimal character to a binary string
// Does not append NULL at end of the binary string
void hex_to_bin(char hex, char *bin) {
   unsigned int i = strtoul(&hex, NULL, 16);

   strncpy(bin, hex_binary[i], 4);
}

// Convert a hexedecimal string to the corresponding char array
void hex_to_ascii(const char *hex, unsigned char *ascii) {
   int len = strlen(hex) / 2;
   char tmp[3];
   tmp[2] = '\0';

   for (int i = 0; i < len; ++i) {
      tmp[0]   = hex[2 * i];
      tmp[1]   = hex[2 * i + 1];
      ascii[i] = (unsigned char)(strtoul(tmp, NULL, 16));
   }
}

// Code for reverse and rotate taken from Stack overflow at https://stackoverflow.com/questions/22078728/rotate-array-left-or-right-by-a-set-number-of-positions-in-on-complexity
// Algorithm described by Jon Bentley in Programming Pearls Column 2

// Reverses a char array of tlength len
void reverse(char *arr, int len) {
   int i, j;

   for (i = 0, j = len; i < j; ++i, --j) {
      char tmp = arr[i];
      arr[i] = arr[j];
      arr[j] = tmp;
   }
}

// Rotates an array of length len the specified amount.
// Negative number correspond to left rotation.
// The algorithm splits the array according to amt, then reverse each half
// seperately followed by reversing the whole array.
void rotate(char *arr, int len, int amt) {
   if (amt < 0) {
      amt = len + amt;
   }
   reverse(arr, len - amt - 1);
   reverse(arr + len - amt, amt - 1);
   reverse(arr, len - 1);
}
