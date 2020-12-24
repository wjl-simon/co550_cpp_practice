#include "soundex.h"
#include <cctype>
#include <cstring>

using namespace std;

#define SDX_LEN 4
#define MAX_STR_LEN 100

void encode(const char* surname, char soundex[])
{
  int j = 0; // position count for surname
  char sur[MAX_STR_LEN]; strcpy(sur, surname);
  eli_ignored(sur);
  eli_identical(sur);// normalising the string

  char digit = '0';
  
  for(int i = 0; i <= SDX_LEN ; i++)
    {
      if(i == 0)
        {
          soundex[i] = toupper(sur[j++]);
        }
      else if(i < SDX_LEN)
        {
          digit = mapping(sur[j]);

          if(sur[j] != '\0') j++;

          soundex[i] = digit; // write the soundex

        }
      else
        soundex[i] = '\0';
    }
}


char mapping(char ch)
{   
  if(!isalpha(ch)) return '0'; // the '\0' etc

  //convert the ch into upper form
  ch = toupper(ch);
  
  switch(ch)
  {
  case 'B':
  case 'F':
  case 'P':
  case 'V': return '1';

  case 'C':
  case 'G':
  case 'J':
  case 'K':
  case 'Q':
  case 'S':
  case 'X':
  case 'Z': return '2';

  case 'D':
  case 'T': return '3';

  case 'L': return '4';

  case 'M':
  case 'N': return '5';

  case 'R': return '6';

  default: return 'B'; // the ignored ones
  }
}

// normalise the string s.t. ignoring all the occurence of some letters
void eli_ignored(char surname[], int count)
{
  if(surname[count] == '\0') return;
  else
    {
      if(count > 0)
        {
          if(mapping(surname[count]) == 'B')
            {
              for(int i = count; surname[i]!= '\0'; i++)
                surname[i] = surname[i+1];

              eli_ignored(surname, count);
            }
          else
            eli_ignored(surname, ++count);
        }
      else // count == 0
        eli_ignored(surname, ++count);
    }
}

// treating the adjacent letters that produce identical numbers as one letter
void eli_identical(char surname[], int count)
{
  if(surname[count] == '\0') return; // base case
  else
    {
      // if the next char has the same soundex digit: skip!
      if(count > 0)
        {
          // shift and override the duplicated letters
          if(mapping(surname[count]) == mapping(surname[count+1]))
            {
              for(int i = count + 1; surname[i]!= '\0'; i++)
                surname[i] = surname[i+1];

              eli_identical(surname, count);
            }
          else
            eli_identical(surname, ++count);
        }
      else // count == 0
        eli_identical(surname, ++count);
    }
}

bool compare(const char* one, const char* two)
{
  // base case
  if(*one == '\0' && *two == '\0') return true;
    
  if(*one == *two)
    {
      if(compare(one+1,two+1))
        return true;
      else
        return false;
    }
  else return false;
}


// Q3: version 1, iterative
/*
int count(const char* surname, const char* sentence)
{
  char sen[MAX_STR_LEN]; strcpy(sen,sentence);
  char sur_code [SDX_LEN + 1]; encode(surname,sur_code);

  char word[MAX_STR_LEN]; char encoded[SDX_LEN + 1];
  
  int counter = 0, acc_offset = 0; // accumulated offset
  while(extract_word(sen+acc_offset, word, acc_offset))
    {
      encode(word,encoded);
      if(compare(sur_code,encoded)) counter++;
    }

  return counter;
}

bool extract_word(char sen[], char out[], int& offset)
{
  // locate the fist letter
  while(isalpha(*sen) == 0)
    {
      if(*sen != '\0')
        {
          sen++;
          offset++;
        }
      else // there's no letter left
        return false;
    }

  // extract the word
  int i = 0;
  while(isalpha(*sen) != 0)
    {
      out[i++] = *sen;
      sen++;
      offset++;
    }
  out[i] = '\0';
  return true;
}
*/

// Q3: version 2: recursive
int count_solver(const char* sur_code, char* sen, int counter)
{
  // locate the fist letter
  while(isalpha(*sen) == 0)
    {
      if(*sen != '\0')
        sen++;
      else // there's no letter left
        return counter;
    }

  // extract the word
  int i = 0;
  char word[MAX_STR_LEN]; char encoded[SDX_LEN + 1];

  while(isalpha(*sen) != 0)
    {
      word[i++] = *sen;
      sen++;
    }
  word[i] = '\0';

  // compare and update
  encode(word,encoded);
  if(compare(sur_code,encoded)) counter++;

  // recursion
  return count_solver(sur_code, sen, counter);
}


int count(const char* surname, const char* sentence)
{
  char sen[MAX_STR_LEN]; strcpy(sen,sentence);
  char sur_code [SDX_LEN + 1]; encode(surname,sur_code);

  int counter = 0;
  return count_solver(sur_code,sen,counter);
}
