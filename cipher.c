/*
 *  Donovan Ellison
 *  06-21-2019
 *
 *  cipher.c - Code to encrypt and decrypt a string
 */

#include "block_cipher.h"

// Function to read the specified file and store it in output.
// Return the length of the string
int read_file(char *filename, char *output) {
   FILE *fptr = fopen(filename, "r");
   char  ch;

   if (fptr == NULL) {
      printf("File does not exists \n");
      return(0);
   }

   ch = fgetc(fptr);
   int i = 0;
   while (ch != EOF) {
      output[i] = ch;
      ch        = fgetc(fptr);
      ++i;
   }
   output[i] = '\0';

   fclose(fptr);
   return(i);
}

// Function to write the input string to a file
void write_file(char *filename, char *input) {
   FILE *fptr = fopen(filename, "w");

   if (fptr == NULL) {
      printf("File does not exists \n");
      return;
   }

   fprintf(fptr, "%s", input);
   fclose(fptr);
}

// Function to read plaintext and a key from local files, encrypt it, and
// store the result in ciphertext.txt
void encrypt() {
   char           plaintext[200], hex_key[21];
   unsigned char *ciphertext = NULL;
   int            len;

   // Read the plaintext and key and print it
   len = read_file("input/plaintext.txt", plaintext);
   read_file("input/key.txt", hex_key);
   hex_key[20] = '\0';

   printf("Plaintext: %s", plaintext);
   printf("Key: %s\n", hex_key);

   if (encrypt_ecb(plaintext, len, hex_key, &ciphertext)) {
      printf("Ciphertext: %s\n", ciphertext);
      write_file("input/ciphertext.txt", ciphertext);
      free(ciphertext);
   }
   else {
      printf("Failed to encrypt\n");
      if (ciphertext) {
         free(ciphertext);
      }
   }
}

// Function to read ciphertext and a key from local files, decrypt it, and
// store the result in plaintext.txt
void decrypt() {
   char           ciphertext[200], hex_key[21];
   unsigned char *plaintext = NULL;
   int            len;

   // Read the ciphertext and key
   len = read_file("input/ciphertext.txt", ciphertext);
   read_file("input/key.txt", hex_key);
   hex_key[20] = '\0';
   printf("Ciphertext: %s\n", ciphertext);
   printf("Key: %s\n", hex_key);

   // Decrypt the ciphertext in 64 bit blocks and store it in plaintext.txt
   if (decrypt_ecb(ciphertext, len, hex_key, &plaintext)) {
      printf("Plaintext: %s", plaintext);
      write_file("input/plaintext.txt", plaintext);
   }
   else {
      printf("Failed to decrypt\n");
      if (plaintext) {
         free(plaintext);
      }
   }
   // hex_to_ascii(hex_key, key);
   // int len = strlen(ciphertext);
   // for (i = 0; i < len; i += 8) {
   //       memcpy(temp, ciphertext+i, 8);
   //       decryption(temp, key);
   //       memcpy(plaintext+i, temp, 8);
   // }
}

int main(int argc, char *argv[]) {
   if (argc < 2) {
      printf("Please specify wether you wish to encrypt or decrypt:\n \
        ./cipher encrypt\n \
        ./cipher decrypt\n");
      return(0);
   }

   if (!strcmp(argv[1], "encrypt")) {
      printf("\nEncrypting...\n");
      encrypt();
   }
   else if (!strcmp(argv[1], "decrypt")) {
      printf("\nDecrypting...\n");
      decrypt();
   }
   else{
      printf("Please specify wether you wish to encrypt or decrypt:\n \
        ./cipher encrypt\n \
        ./cipher decrypt\n");
   }

   return(0);
}
