#include "braille.h"
#include <cctype>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

#define MAX_BRA_LEN 12
#define BRA_LEN 6
#define MAX_STR_LEN 512

int encode_upper(char ch, char braille[])
{
  // preceding symbol
  strcpy(braille, ".....0");

  // append the lower case equivalent
  encode_lower(tolower(ch), braille+6);
  return MAX_BRA_LEN;
}

int encode_lower(char ch, char* braille)
{
  switch(ch)
    {
    case 'a':
      strcpy(braille, "0....."); break;
    case 'b':
      strcpy(braille, "00...."); break;
    case 'c':
      strcpy(braille, "0..0.."); break;
    case 'd':
      strcpy(braille, "0..00."); break;
    case 'e':
      strcpy(braille, "0...0."); break;
    case 'f':
      strcpy(braille, "00.0.."); break;
    case 'g':
      strcpy(braille, "00.00."); break;
    case 'h':
      strcpy(braille, "00..0."); break;
    case 'i':
      strcpy(braille, ".0.0.."); break;
    case 'j':
      strcpy(braille, ".0.00."); break;
    case 'k':
      strcpy(braille, "0.0..."); break;
    case 'l':
      strcpy(braille, "000..."); break;
    case 'm':
      strcpy(braille, "0.00.."); break;
    case 'n':
      strcpy(braille, "0.000."); break;
    case 'o':
      strcpy(braille, "0.0.0."); break;
    case 'p':
      strcpy(braille, "0000.."); break;
    case 'q':
      strcpy(braille, "00000."); break;
    case 'r':
      strcpy(braille, "000.0."); break;
    case 's':
      strcpy(braille, ".000.."); break;
    case 't':
      strcpy(braille, ".0000."); break;
    case 'u':
      strcpy(braille, "0.0..0"); break;
    case 'v':
      strcpy(braille, "000..0"); break;
    case 'w':
      strcpy(braille, ".0.000"); break;
    case 'x':
      strcpy(braille, "0.00.0"); break;
    case 'y':
      strcpy(braille, "0.0000"); break;
    case 'z':
      strcpy(braille, "0.0.00"); break;
    }
  return BRA_LEN;
}

int encode_digit(char ch, char* braille)
{
  // preceding symbol
  strcpy(braille, "..0000");

  // append the lower case equivalent
  if(ch != '0')
    encode_lower(static_cast<char>(ch-'0'+'a'-1), braille+6);
  else
    encode_lower('j', braille+6);

   return MAX_BRA_LEN;
}

int encode_punct(char ch, char* braille)
{
  switch(ch)
    {
    case '.':
      strcpy(braille, ".0..00"); break;
    case ';':
      strcpy(braille, ".00..."); break;
    case '-':
      strcpy(braille, "..0..0"); break;
    case '!':
      strcpy(braille, ".00.0."); break;
    case '?':
      strcpy(braille, ".00..0"); break;
    case '(':
    case ')':
      strcpy(braille, ".00.00"); break;
    default:
      strcpy(braille, "......");
    }
  return BRA_LEN;
}

int encode_character(char ch, char braille[])
{
  // identify if ch is a letter/digit/punct
  if(isalpha(ch))
    {
      if(isupper(ch))
        return encode_upper(ch,braille);
      else
        return encode_lower(ch,braille);
    }
  else if(isdigit(ch))
    return encode_digit(ch,braille);
  else if(ispunct(ch))
    return encode_punct(ch,braille);
  else
    {
      strcpy(braille, "......");
      return BRA_LEN;
    }
  
}

void encode(const char* plaintext, char braille[])
{
  if(*plaintext == '\0') return; // base case

  int size = encode_character(*plaintext, braille);

  encode(plaintext+1,braille+size);
}


void print_braille(const char* plaintext, ostream& output)
{
  char encoded[MAX_BRA_LEN+1];

  const int LEN = strlen(plaintext);
  char braille[LEN*2][M][N]; int size = 0;

  // make brailles
  for(int k = 0; k < 2*LEN; k = k+2)
    {
      size = encode_character(plaintext[k/2], encoded);
      
      // the first symbol of the encoded symbol
      for(int j = 0; j < N; j++)
        {
          for(int i = 0; i < M; i++)
            braille[k][i][j] = encoded[j*M + i];
        }

      // the second symbol
      for(int j = 0; j < N; j++)
        {
          for(int i = 0; i < M; i++)
            {
              if(size == MAX_BRA_LEN)
                braille[k+1][i][j] = encoded[M*N + j*M + i];
              else
                braille[k+1][i][j] = '\0';
            }
        }
        
    }

  // print
  for(int i = 0; i < M; i++)
    {
      for(int k = 0; k < 2*LEN; k++)
        {
          for(int j = 0; j < N; j++)
            output << braille[k][i][j];

          if(braille[k][i][0] !='\0')
            output << ' ';
          
          // new line
          if(k == 2*LEN-1) output << endl;
        }
    }

  // the last row
  for(int k = 0; k < LEN; k++)
    {
      if(isupper(plaintext[k]) || isdigit(plaintext[k]))
        output << ' ' << ' ' << ' ';
      
      output << plaintext[k] << ' ' << ' ';
    }
  output << endl;
}

