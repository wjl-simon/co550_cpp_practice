#ifndef CORRECT_H
#define CORRECT_H

#include <cstring>

void ascii_to_binary(char letter, char *output);
char binary_to_ascii(const char *binary);

// Q1
void text_to_binary(const char* text, char* binary, int pos = 0);

void binary_to_text(const char* binary, char* str);


// Q2
void add_error_correction(const char* data, char* corrected);

char parity(char d1, char d2, char d3);


// Q3
int decode(const char* received, char* decoded);
char parity(char b1, char b2, char b3, char b4);


int bin_to_dec(const char* bin);

bool decode_1_cw(char* codeword, char* data);

#endif
