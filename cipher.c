/*
    Donovan Ellison
    11-28-2018

    test_present.c - Code to test functions for ECC
*/

#include "present.h"

// Function to read the specified file and store it in output.
void read_file(char *filename, char *output) {
    FILE *fptr = fopen(filename, "r");
    char ch;

    if (fptr == NULL)
    {
        printf("File does not exists \n");
        return;
    }

    ch = fgetc(fptr);
    int i = 0;
    while (ch != EOF){
        output[i] = ch;
        ch = fgetc(fptr);
        ++i;
    }
    output[i] = '\0';

    fclose(fptr);
}

// Function to write the input string to a file
void write_file(char *filename, char *input) {
    FILE *fptr = fopen(filename, "w");

    if (fptr == NULL)
    {
        printf("File does not exists \n");
        return;
    }

    fprintf(fptr, "%s", input);
    fclose(fptr);
}

// Function to read plaintext and a key from local files, encrypt it, and
// store the result in ciphertext.txt
void encrypt() {
    char plaintext[200], ciphertext[200], hex_key[21];
    unsigned char temp[9], key[11];
    int i;

    // Read the plaintext and key and print it
    read_file("plaintext.txt", plaintext);
    read_file("key.txt", hex_key);
    printf("Plaintext: %s", plaintext);
    printf("Key: %s", hex_key);

    hex_to_ascii(hex_key, key);
    int len = strlen(plaintext);

    // If the plaintext is not in 64-bit blocks, pad with 0 bits
    if (len % 8 != 0) {
        int rem = len % 8;
        for (i = 0; i < rem; ++i)
            plaintext[len+i] = '\x00';
        plaintext[len+rem] = '\0';
        len = strlen(plaintext);
    }
    else
        ciphertext[len] = '\0';

    // Encrypt 64-bits at a time and store it in ciphertext.txt
    for (i = 0; i < len; i += 8) {
        memcpy(temp, plaintext+i, 8);
        encryption(temp, key);
        memcpy(ciphertext+i, temp, 8);
    }
    printf("Ciphertext: %s", ciphertext);
    write_file("ciphertext.txt", ciphertext);
}

// Function to read ciphertext and a key from local files, decrypt it, and
// store the result in plaintext.txt
void decrypt() {
    char ciphertext[200], plaintext[200], hex_key[21];
    unsigned char temp[8], key[10];
    int i;

    // Read the ciphertext and key
    read_file("ciphertext.txt", ciphertext);
    read_file("key.txt", hex_key);
    printf("Ciphertext: %s\n", ciphertext);
    printf("Key: %s", hex_key);

    // Decrypt the ciphertext in 64 bit blocks and store it in plaintext.txt
    hex_to_ascii(hex_key, key);
    int len = strlen(ciphertext);
    for (i = 0; i < len; i += 8) {
        memcpy(temp, ciphertext+i, 8);
        decryption(temp, key);
        memcpy(plaintext+i, temp, 8);
    }
    printf("Plaintext: %s", plaintext);
    write_file("plaintext.txt", plaintext);

}

int main(int argc, char * argv[])
{
    if (argc < 2)
    {
        printf("Please specify wether you wish to encrypt or decrypt:\n \
        ./cipher encrypt\n \
        ./cipher decrypt\n");
        return 0;
    }

    if (!strcmp(argv[1], "encrypt")) {
        printf("\nEncrypting...\n");
        encrypt();
    }
    else if (!strcmp(argv[1], "decrypt")) {
        printf("\nDecrypting...\n");
        decrypt();
    }
    else
        printf("Please specify wether you wish to encrypt or decrypt:\n \
        ./cipher encrypt\n \
        ./cipher decrypt\n");

    return 0;
}
