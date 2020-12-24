#ifndef PIGLATIN_H
#define PIGLATIN_H

#include <iostream>
#include <fstream>

//Q1
// return pos of the first vowel
int findFirstVowel(const char* word);

bool isVowel(char ch, int pos, int len);


// Q2
void translateWord(const char* english, char* piglatin);

//Q3
void translateStream(std::istream& inputStream, std::ostream& outputStream);

int containPunct(const char* word);
#endif
