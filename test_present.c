/*
    Donovan Ellison
    11-28-2018

    test_present.c - Code to test functions for ECC
*/

#include "present.h"

void print_hex(unsigned char * str) {
    for (int i = 0; i < 8; ++i)
        printf("%02X ", str[i]);
}

void print_10_hex(unsigned char * str) {
    for (int i = 0; i < 10; ++i)
        printf("%02X ", str[i]);
}

void test_add_round_key(unsigned char *state, unsigned char *key, unsigned char *target) {
    printf("\n\t%-9s| ", "State");
    print_hex(state);
    printf("\n\t%-9s| ", "Key");
    print_hex(key);
    add_round_key(state, key);

    printf("\n\t%-9s| ", "Expected");
    print_hex(target);
    printf("\n\t%-9s| ", "Actual");
    print_hex(state);
}

void test_s_box_layer(unsigned char *state, unsigned char *target, bool inverse) {
    printf("\n\t[%s]", inverse ? "Inverse" : "Regular");
    printf("\n\t%-9s| ", "State");
    print_hex(state);
    s_box_layer(state, inverse);

    printf("\n\t%-9s| ", "Expected");
    print_hex(target);
    printf("\n\t%-9s| ", "Actual");
    print_hex(state);
}

void test_p_layer(unsigned char *state, unsigned char *target, bool inverse) {
    printf("\n\t[%s]", inverse ? "Inverse" : "Regular");
    printf("\n\t%-9s| ", "State");
    print_hex(state);
    p_layer(state, inverse);

    printf("\n\t%-9s| ", "Expected");
    print_hex(target);
    printf("\n\t%-9s| ", "Actual");
    print_hex(state);
}

void test_generate_round_key(unsigned char *key, unsigned char *target, int counter) {
    printf("\n\t[Round %d]", counter);
    printf("\n\t%-9s| ", "Key");
    print_10_hex(key);
    generate_round_key(key, counter);

    printf("\n\t%-9s| ", "Expected");
    print_10_hex(target);
    printf("\n\t%-9s| ", "Actual");
    print_10_hex(key);
}

void test_cipher(unsigned char *state, unsigned char *key, unsigned char *target) {
    printf("\n\t%-9s| ", "State");
    print_hex(state);
    printf("\n\t%-9s| ", "Key");
    print_10_hex(key);
    printf("\n\t%-9s| ", "Expected");
    print_hex(target);

    encryption(state, key);
    printf("\n\t%-9s| ", "Encrypt");
    print_hex(target);

    decryption(state, key);
    printf("\n\t%-9s| ", "Decrypt");
    print_hex(state);
}



int main(int argc, char * argv[])
{
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

    // printf("\n\n----------------Testing str_to_bin---------------------\n\n");
    // unsigned char test[] = "ABC";
    // char binary[24];
    // str_to_bin(test, binary, 3);
    // printf("ABC    -> %s\n", binary);
    // printf("Expected: 010000010100001001000011\n");

    // printf("\n\n----------------Testing bin_to_str---------------------\n\n");
    // bin_to_str(test, "010000110100001001000001", 3);
    // printf("010000110100001001000001 -> %s\n", test);
    // printf("Expected: CBA\n");

    // printf("\n\n----------------Testing hex_to_bin---------------------\n\n");
    // printf("%s\n", hex_to_bin('A'));

    return 0;
}
