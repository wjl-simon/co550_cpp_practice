#ifndef SOUNDEX_H
#define SOUNDEX_H

void encode(const char* surname, char soundex[]);

char mapping(char ch);


void eli_ignored(char surname[], int count = 0);

void eli_identical(char surname[], int count = 0);

bool compare(const char* one, const char* two);

/*
bool extract_word(char sen[], char out[], int& offset);

int count(const char* surname, const char* sentence);
*/


int count(const char* surname, const char* sentence);

int count_solver(const char* sur_code, char* sen, int counter);

#endif
