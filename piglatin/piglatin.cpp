#include "piglatin.h"
#include <cctype>
#include <cstring>

using namespace std;

#define MAX_STR_LEN 64

bool isVowel(char ch, int position, int length)
{
  if(!isalpha(ch)) return false;

  ch = tolower(ch);

  if(ch == 'a' || ch == 'e' || ch == 'i' ||
     ch == 'o' || ch == 'u')
    return true;

  // 'y' is an vowel if not at the head nor the end
  if(ch == 'y')
    {
      if(position == 0 || position == length-1)
        return false;
      else
        return true;
    }

  return false;
}


// Q1: recursive version

int findFirstVowel(const char* word)
{ 
  const int LEN = strlen(word);

  return firstVowelSol(word,0,LEN);
}

int firstVowelSol(const char* word, int pos, int len)
{
  // base case 1: word starting with a digit: leave it
  //if(isdigit(*word) && pos == 0) return -1;

  // base case 2
  if(*word == '\0') return -1;

  // base case 3
  if(isVowel(*word, pos, len)) return pos;
  else
    return firstVowelSol(word+1, pos+1, len);
}


// Q1: iterative version
/*
int findFirstVowel(const char* word)
{
  const int LEN = strlen(word);
  for(int i = 0; i < LEN; i++)
    {
      if(isVowel(word[i], i, LEN))
        return i;
    }

  return -1;
}
*/

void translateWord(const char* english, char piglatin[])
{
  // begins with a digit: leave it
  if(isdigit(*english))
    {
      strcpy(piglatin, english);
      return;
    }
    
  int firstVowPos = findFirstVowel(english);
  const int LEN = strlen(english);
  
  // has a vowel
  if(firstVowPos != -1)
    {
      // the word begins with a vowel
      if(firstVowPos == 0)
        {
          strcpy(piglatin, english);
          strcpy(piglatin+LEN,"way");
          return;
        }

      // begins with non-vowel:
      bool upperFlag = false;
      if(isupper(*english)) upperFlag = true; // english[0] is capital?
      
      char head[MAX_STR_LEN]; // the substring before the first vowel
      for(int i = 0; i <= firstVowPos; i++)
        {
          if(i == 0 && upperFlag == true)
            head[i] = tolower(english[i]);
          else if(i < firstVowPos)
            head[i] = english[i];
          else
            head[i] = '\0';
        }

      // copy the substring starting from the first vowel
      strcpy(piglatin, english+firstVowPos);
      if(upperFlag) piglatin[0] = toupper(piglatin[0]);
      // append the head
      int curLen = strlen(piglatin);
      strcpy(piglatin+curLen,head);
      // append "ay"
      curLen = strlen(piglatin);
      strcpy(piglatin+curLen,"ay");
      
      return;
    }
  else // has no vowel
    {
      strcpy(piglatin, english);
      strcpy(piglatin+LEN,"ay");
      return;
    }
}


void translateStream(istream& inputStream, ostream& outputStream)
{
  char word[MAX_STR_LEN+1];
  inputStream >> word;
  if(strcmp(word,"") == 0) return; // base case

  // test if there is a punctuation at the beginning/end of the word
  char punct;
  int code = removePunct(word,punct);

  // translate the word
  char translated[MAX_STR_LEN+1];
  translateWord(word,translated);

  if(code == 1)
    outputStream << punct << translated << " ";
  else if(code == 2)
    outputStream << translated << punct << endl;
  else
    outputStream << translated << " ";
  
  translateStream(inputStream,outputStream);
}


int removePunct(char str[], char& out)
{
  const int LEN = strlen(str);

  // the beginning has a punct
  if(ispunct(*str))
    {
      out = *str; 
      for(int i = 0; i < LEN; i++)
        str[i] = str[i+1];

      return 1;
    }

  // the end has a punct
  if(ispunct(*(str+LEN-1)))
    {
      out = *(str+LEN-1);
      str[LEN-1] = '\0';

      return 2;
    }

  return 0;
}
