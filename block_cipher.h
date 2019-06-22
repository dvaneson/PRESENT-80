/*
    Donovan Ellison
    06-21-2019

    block_cipher.h - Header for block cipher modes of operation
 */

 #include "present.h"

void encrypt_ecb(const char *, const char *, unsigned char **);
char* decrypt_ecb(char *, char *);
