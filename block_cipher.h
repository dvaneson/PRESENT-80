/*
 *  Donovan Ellison
 *  06-21-2019
 *
 *  block_cipher.h - Header for block cipher modes of operation
 */

#include "present.h"

// Encrypt using ECB mode of operation
bool encrypt_ecb(const char *, int, const char *, unsigned char **);

// Decrypt using ECB mode of operation
bool decrypt_ecb(const char *, int, const char *, unsigned char **);
