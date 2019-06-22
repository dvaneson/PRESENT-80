/*
    Donovan Ellison
    06-21-2019

    block_cipher.c - Implementation of block cipher modes of operations
*/

#include "block_cipher.h"

// Encrypt an arbitrary string with PRESENT-80, using the Electronic Codebook
// (ECB) mode of operation
// plaintext -> a char array of the plaintext
// len -> the length of the plaintext
// hex_key -> 20 hexadecimal numbers, represented by a string
// ciphertext -> NULL char array that the ciphertext will be stored in.
// Must deallocate ciphertext after use
bool encrypt_ecb(const char *plaintext, int len, const char *hex_key, unsigned char **ciphertext) {
  // Make sure hexadecimal key is correct length
  if (strlen(hex_key) != 20) {
    return false;
  }

  int rem = len < 8 ? 8 % len : 8 - (len % 8);
  int blocks = (len + rem) / 8;
  unsigned char key[10];
  hex_to_ascii(hex_key, key);

  // Make ciphertext as large or larger than plaintext, to be a multiple of 8
  *ciphertext = NULL;
  *ciphertext = (unsigned char*) malloc((blocks*8 + 1) * sizeof(unsigned char));
  memcpy(*ciphertext, plaintext, len);

  // Pad the extra spaces with NULL terminator
  for (int i = 0; i < rem; ++i) {
    (*ciphertext)[len+i] = '\0';
  }

  // Encrypt each block
  for (int i = 0; i < blocks; ++i) {
    encryption((*ciphertext)+i*8, key);
  }
  (*ciphertext)[len+rem] = '\0';

  return true;
}

// Decrypt ciphertext with PRESENT-80, using the Electronic Codebook
// (ECB) mode of operation
// ciphertext -> a char array of the ciphertext
// len -> the length of the ciphertext
// hex_key -> 20 hexadecimal numbers, represented by a string
// plaintext -> NULL char array that the plaintext will be stored in.
// Must deallocate plaintext after use
bool decrypt_ecb(const char *ciphertext, int len, const char *hex_key, unsigned char **plaintext) {
  // Make sure hexadecimal key is correct length
  if (strlen(hex_key) != 20) {
    return false;
  }

  int blocks = len / 8;
  unsigned char key[10];
  hex_to_ascii(hex_key, key);

  *plaintext = NULL;
  *plaintext = (unsigned char*) malloc((blocks*8 + 1) * sizeof(unsigned char));
  memcpy(*plaintext, ciphertext, len);

  for (int i = 0; i < blocks; ++i) {
    decryption((*plaintext)+i*8, key);
  }
  (*plaintext)[len] = '\0';

  return true;
}
