/*
 *  Donovan Ellison
 *  11-28-2018
 *
 *  test_present.c - Code to test functions for ECC
 */

#include <bsd/string.h>
#include "present.h"

void print_hex(unsigned char *str) {
   for (int i = 0; i < 8; ++i) {
      printf("%02X ", str[i]);
   }
}

void print_10_hex(unsigned char *str) {
   for (int i = 0; i < 10; ++i) {
      printf("%02X ", str[i]);
   }
}

void test_add_round_key(unsigned char *state, unsigned char *key, unsigned char *target) {
   unsigned char actual[8];

   memcpy(actual, state, 8);

   add_round_key(actual, key);
   if (memcmp(actual, target, 8) != 0) {
      printf("\n\t%-9s| ", "State");
      print_hex(state);
      printf("\n\t%-9s| ", "Key");
      print_hex(key);

      printf("\n\t%-9s| ", "Expected");
      print_hex(target);
      printf("\n\t%-9s| ", "Actual");
      print_hex(actual);
   }
   else {
      printf("\n\tPASSED");
   }
}

void test_s_box_layer(unsigned char *state, unsigned char *target, bool inverse) {
   unsigned char actual[8];

   memcpy(actual, state, 8);

   s_box_layer(actual, inverse);
   if (memcmp(actual, target, 8) != 0) {
      printf("\n\t[%s]", inverse ? "Inverse" : "Regular");
      printf("\n\t%-9s| ", "State");
      print_hex(state);

      printf("\n\t%-9s| ", "Expected");
      print_hex(target);
      printf("\n\t%-9s| ", "Actual");
      print_hex(actual);
   }
   else {
      printf("\n\tPASSED");
   }
}

void test_p_layer(unsigned char *state, unsigned char *target, bool inverse) {
   unsigned char actual[8];

   memcpy(actual, state, 8);

   p_layer(actual, inverse);
   if (memcmp(actual, target, 8) != 0) {
      printf("\n\t[%s]", inverse ? "Inverse" : "Regular");
      printf("\n\t%-9s| ", "State");
      print_hex(state);

      printf("\n\t%-9s| ", "Expected");
      print_hex(target);
      printf("\n\t%-9s| ", "Actual");
      print_hex(actual);
   }
   else {
      printf("\n\tPASSED");
   }
}

void test_generate_round_key(unsigned char *key, unsigned char *target, int counter) {
   unsigned char actual[10];

   memcpy(actual, key, 10);

   generate_round_key(actual, counter);
   if (memcmp(actual, target, 10) != 0) {
      printf("\n\t[Round %d]", counter);
      printf("\n\t%-9s| ", "Key");
      print_10_hex(key);

      printf("\n\t%-9s| ", "Expected");
      print_10_hex(target);
      printf("\n\t%-9s| ", "Actual");
      print_10_hex(actual);
   }
   else {
      printf("\n\tPASSED");
   }
}

void test_cipher(unsigned char *state, unsigned char *key, unsigned char *target) {
   unsigned char encrypted[8], decrypted[8];

   memcpy(encrypted, state, 8);
   encryption(encrypted, key);

   memcpy(decrypted, encrypted, 8);
   decryption(decrypted, key);

   if (memcmp(encrypted, target, 8) != 0 || memcmp(decrypted, state, 8) != 0) {
      printf("\n\t%-9s| ", "State");
      print_hex(state);
      printf("\n\t%-9s| ", "Key");
      print_10_hex(key);
      printf("\n\t%-9s| ", "Expected");
      print_hex(target);

      printf("\n\t%-9s| ", "Encrypted");
      print_hex(encrypted);

      printf("\n\t%-9s| ", "Decrypted");
      print_hex(decrypted);
   }
   else {
      printf("\n\tPASSED");
   }
}

void test_str_to_bin(unsigned char *str, unsigned char *target) {
   char bin[25];
   int  len = strlen(str);

   str_to_bin(str, bin, len);
   bin[len * BLOCK_LENGTH] = '\0';
   if (strcmp(bin, target) != 0) {
      printf("\n\t%-9s| %s", "Input", str);
      printf("\n\t%-9s| %s", "Expected", target);
      printf("\n\t%-9s| %s", "Actual", bin);
   }
   else {
      printf("\n\tPASSED");
   }
}

void test_bin_to_str(unsigned char *bin, unsigned char *target) {
   char str[4];
   int  len = strlen(bin) / BLOCK_LENGTH;

   bin_to_str(str, bin, len);
   str[len] = '\0';
   if (strcmp(str, target) != 0) {
      printf("\n\t%-9s| %s", "Input", bin);
      printf("\n\t%-9s| %s", "Expected", target);
      printf("\n\t%-9s| %s", "Actual", str);
   }
   else {
      printf("\n\tPASSED");
   }
}

void test_hex_to_bin(char hex, char *target) {
   char bin[5];

   hex_to_bin(hex, bin);
   bin[4] = '\0';
   if (strcmp(bin, target)) {
      printf("\n\t%-9s| %c", "Input", hex);
      printf("\n\t%-9s| %s", "Expected", target);
      printf("\n\t%-9s| %s", "Actual", bin);
   }
   else {
      printf("\n\tPASSED");
   }
}

int main(int argc, char *argv[]) {
   char str[4];
   char bin[25], hex[5];

   /* Testing utility Functions */
   printf("\n\n----------------Testing str_to_bin---------------------\n");
   strlcpy(str, "A", 2);
   strlcpy(bin, "01000001", 9);
   test_str_to_bin(str, bin);

   printf("\n");
   strlcpy(str, "CBA", 4);
   strlcpy(bin, "010000110100001001000001 ", 25);
   test_str_to_bin(str, bin);

   printf("\n");
   strlcpy(str, "ABC", 4);
   strlcpy(bin, "010000010100001001000011", 25);
   test_str_to_bin(str, bin);

   printf("\n\n----------------Testing bin_to_str---------------------\n");
   strlcpy(str, "A", 2);
   strlcpy(bin, "01000001", 9);
   test_bin_to_str(bin, str);

   printf("\n");
   strlcpy(str, "CBA", 4);
   strlcpy(bin, "010000110100001001000001 ", 25);
   test_bin_to_str(bin, str);

   printf("\n");
   strlcpy(str, "ABC", 4);
   strlcpy(bin, "010000010100001001000011", 25);
   test_bin_to_str(bin, str);

   printf("\n\n----------------Testing hex_to_bin---------------------\n");
   strlcpy(bin, "0000", 5);
   test_hex_to_bin('0', bin);

   printf("\n");
   strlcpy(bin, "1001", 5);
   test_hex_to_bin('9', bin);

   printf("\n");
   strlcpy(bin, "1010", 5);
   test_hex_to_bin('A', bin);

   printf("\n");
   strlcpy(bin, "1111", 5);
   test_hex_to_bin('F', bin);


   /* Testing functions directly related to encryption/decryption */

   unsigned char state[8], key[8], target[8];

   printf("\n----------------Testing add_round_key----------------\n");
   memcpy(state, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
   memcpy(key, "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 8);
   memcpy(target, "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 8);
   test_add_round_key(state, key, target);

   printf("\n");
   memcpy(state, "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 8);
   memcpy(key, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
   memcpy(target, "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 8);
   test_add_round_key(state, key, target);

   printf("\n");
   memcpy(state, "\x2E\x54\x86\x84\x7B\x1E\xE1\x04", 8);
   memcpy(key, "\x02\xA5\x5A\x69\xD8\x42\xBA\x28", 8);
   memcpy(target, "\x2C\xF1\xDC\xED\xA3\x5C\x5B\x2C", 8);
   test_add_round_key(state, key, target);


   printf("\n\n----------------Testing s_box_layer------------------\n");
   memcpy(state, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
   memcpy(target, "\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC", 8);
   test_s_box_layer(state, target, false);

   printf("\n");
   memcpy(state, "\x01\x23\x45\x67\x89\xAB\xCD\xEF", 8);
   memcpy(target, "\xC5\x6B\x90\xAD\x3E\xF8\x47\x12", 8);
   test_s_box_layer(state, target, false);

   printf("\n");
   memcpy(state, "\xDA\x6A\xF3\xBD\xF5\xB1\x33\x72", 8);
   memcpy(target, "\x7F\xAF\x2B\x87\x20\x85\xBB\xD6", 8);
   test_s_box_layer(state, target, false);

   printf("\n");
   memcpy(state, "\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC", 8);
   memcpy(target, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
   test_s_box_layer(state, target, true);

   printf("\n");
   memcpy(state, "\xC5\x6B\x90\xAD\x3E\xF8\x47\x12", 8);
   memcpy(target, "\x01\x23\x45\x67\x89\xAB\xCD\xEF", 8);
   test_s_box_layer(state, target, true);

   printf("\n");
   memcpy(state, "\x7F\xAF\x2B\x87\x20\x85\xBB\xD6", 8);
   memcpy(target, "\xDA\x6A\xF3\xBD\xF5\xB1\x33\x72", 8);
   test_s_box_layer(state, target, true);


   printf("\n\n----------------Testing p_layer----------------\n");
   memcpy(state, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
   memcpy(target, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
   test_p_layer(state, target, false);

   printf("\n");
   memcpy(state, "\x01\x23\x45\x67\x89\xAB\xCD\xEF", 8);
   memcpy(target, "\x00\xFF\x0F\x0F\x33\x33\x55\x55", 8);
   test_p_layer(state, target, false);

   printf("\n");
   memcpy(state, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
   memcpy(target, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
   test_p_layer(state, target, true);

   printf("\n");
   memcpy(state, "\x00\xFF\x0F\x0F\x33\x33\x55\x55", 8);
   memcpy(target, "\x01\x23\x45\x67\x89\xAB\xCD\xEF", 8);
   test_p_layer(state, target, true);

   printf("\n\n----------------Testing generate_round_keys----------------\n");
   unsigned char rKey[10], rTarget[10];
   memcpy(rKey, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 10);
   memcpy(rTarget, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 10);
   test_generate_round_key(rKey, rTarget, 0);

   printf("\n");
   memcpy(rKey, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 10);
   memcpy(rTarget, "\xC0\x00\x00\x00\x00\x00\x00\x00\x80\x00", 10);
   test_generate_round_key(rKey, rTarget, 1);

   printf("\n");
   memcpy(rKey, "\x01\x23\x45\x67\x89\xAB\xCD\xEF\x01\x23", 10);
   memcpy(rTarget, "\x10\x24\x60\x24\x68\xAC\xF1\x35\xF9\xBD", 10);
   test_generate_round_key(rKey, rTarget, 1);

   printf("\n\n----------------Testing cipher----------------\n");
   memcpy(state, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
   memcpy(rKey, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 10);
   memcpy(target, "\x55\x79\xC1\x38\x7B\x22\x84\x45", 8);
   test_cipher(state, rKey, target);

   printf("\n");
   memcpy(state, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
   memcpy(rKey, "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 10);
   memcpy(target, "\xE7\x2C\x46\xC0\xF5\x94\x50\x49", 8);
   test_cipher(state, rKey, target);

   printf("\n");
   memcpy(state, "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 8);
   memcpy(rKey, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 10);
   memcpy(target, "\xA1\x12\xFF\xC7\x2F\x68\x41\x7B", 8);
   test_cipher(state, rKey, target);

   printf("\n");
   memcpy(state, "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 8);
   memcpy(rKey, "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 10);
   memcpy(target, "\x33\x33\xDC\xD3\x21\x32\x10\xD2", 8);
   test_cipher(state, rKey, target);

   printf("\n");
   return(0);
}
