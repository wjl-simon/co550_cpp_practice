#ifndef PIGLATIN_H
#define PIGLATIN_H

#include <iostream>
#include <fstream>

bool isVowel(char ch, int position, int length);

int findFirstVowel(const char* word);

int firstVowelSol(const char* word, int pos, int len);

void translateWord(const char* english, char piglatin[]);

void translateStream(std::istream& inputStream, std::ostream& outputStream);

int removePunct(char str[], char& out);

#endif
