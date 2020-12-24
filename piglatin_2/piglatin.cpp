#include "piglatin.h"
#include <cctype>
#include <cstring>

using namespace std;


//Q1
// return pos of the first vowel
int findFirstVowel(const char* word)
{
  const int LEN = strlen(word);
  
  for(int i = 0; i < LEN; i++)
    {
      if(isVowel(word[i],i,LEN)) return i;
    }

  return -1;
}


bool isVowel(char ch, int pos, int len)
{
  char ch_u = toupper(ch);
  
  if(ch_u == 'A' || ch_u == 'E' || ch_u == 'I' ||
     ch_u == 'O' || ch_u == 'U')
    return true;

  if(ch_u == 'Y' && pos != 0 && pos != len-1)
    return true;

  return false;
}

// Q2
#define MAX_STR_LEN 512
void translateWord(const char* english, char* piglatin)
{
  // empty word
  if(strlen(english) == 0)
    {
      piglatin[0] = '\0';
      return;
    }
  
  // word begin with a digit
  if(isdigit(*english))
    {
      strcpy(piglatin,english);
      return;
    }
  
  bool upperHead = false;
  //test if the first word is uppercase
  if(isupper(*english)) upperHead = true;

  // translation
  int firstVolPos = findFirstVowel(english);

  if(firstVolPos == -1) // no vowel at all
    {
      strcpy(piglatin,english);
      strcat(piglatin,"ay");
      
      if(upperHead)
        piglatin[0] = toupper(piglatin[0]);
    }
  else if(firstVolPos == 0) // first vowel at beginning
    {
      strcpy(piglatin,english);
      strcat(piglatin,"way");
      
      if(upperHead)
        piglatin[0] = toupper(piglatin[0]);
    }
  else
    {
      strcpy(piglatin,english+firstVolPos);

      char temp[MAX_STR_LEN]; int i;
      for(i = 0; i < firstVolPos; i++)
        temp[i] = english[i];

      temp[i] = '\0'; temp[0] = tolower(temp[0]);
      strcat(piglatin,temp);
      strcat(piglatin,"ay");
      
      if(upperHead)
        piglatin[0] = toupper(piglatin[0]);
    }
}


//Q3
void translateStream(std::istream& inputStream, std::ostream& outputStream)
{
  // base case
  if(inputStream.eof()) return;

  // get the word
  char word[MAX_STR_LEN]; inputStream >> word;
  const int LEN = strlen(word);
  
  // test if has punctuation
  int pos = containPunct(word);
  char encoded[MAX_STR_LEN];

  char punct;
  
  if(pos == LEN-1) // punct at the end
    {
      punct = word[pos]; // save the punct
      // eliminate the punc
      word[pos] = '\0';
      
      translateWord(word,encoded);
      int len = strlen(encoded);
      encoded[len++] = punct; encoded[len] = '\0'; // append punc

      outputStream << encoded << " " << endl;
    }
  else if(pos == 0) // punct at the beginning
    {
      punct = word[pos];
      // eliminate the punc
      for(int i = 0; word[i]!='\0'; i++)
        word[i] = word[i+1];

      translateWord(word,encoded);
      int len = strlen(encoded);
      for(int i = len; i > 0; i--)
        encoded[i] = encoded[i-1];

      // add the punc at the beginning
      encoded[0] = punct;

      outputStream << encoded << " ";
    }
  else
    {
      translateWord(word,encoded);
      outputStream << encoded << " ";
    }
  
  // recursion
  translateStream(inputStream, outputStream);
}

int containPunct(const char* word)
{
  for(int i = 0; word[i]!='\0'; i++)
    {
      if(ispunct(word[i])) return i;
    }

  return -1;
}
