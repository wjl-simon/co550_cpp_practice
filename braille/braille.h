#ifndef BRAILLE_H
#define BRAILLE_H

#include <iostream>
#include <fstream>

#define M 3
#define N 2

int encode_character(char ch, char* braille);

int encode_digit(char ch, char* braille);

int encode_upper(char ch, char* braille);

int encode_lower(char ch, char* braille);

int encode_punct(char ch, char* braille);

void encode(const char* plaintext, char braille[]);

void print_braille(const char* plaintext, std::ostream& output);
  
#endif
