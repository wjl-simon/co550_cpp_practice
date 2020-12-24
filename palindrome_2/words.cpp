#include "words.h"
#include <cstring>
#include <cctype>

using namespace std;

//Q1
void reverse(const char* str1, char* str2)
{
  const int LEN = strlen(str1);
  int i;
  for(i = 0; i < LEN; i++)
    str2[i] = str1[LEN-i-1];

  str2[i] = '\0';
}

int compare(const char* one, const char* two)
{
  // base case
  if(*one == '\0' || *two == '\0') return 1;

  //recursion
  if(!isalpha(*one) && !isalpha(*two))
    return compare(one+1,two+1);
  else if(!isalpha(*one) && isalpha(*two))
    return compare(one+1,two);
  else if(isalpha(*one) && !isalpha(*two))
    return compare(one,two+1);
  else if(isalpha(*one) && isalpha(*two) && toupper(*one) == toupper(*two))
    {
      if(compare(one+1,two+1)) return 1;
      else return 0;
    }
  else
    return 0;
}

//Q3
#define MAX_STR_LEN 512
int palindrome(const char* sentence)
{
  // the reversed one
  char rev[MAX_STR_LEN] = {};
  reverse(sentence,rev);

  return compare(rev,sentence);
}


//Q4
int anagram(const char* str1, const char* str2)
{
  const int LEN1 = strlen(str1);
  const int LEN2 = strlen(str2);
  
  char str1_c[MAX_STR_LEN]; strcpy(str1_c,str1);
  char str2_c[MAX_STR_LEN]; strcpy(str2_c,str2);

  // sort them out
  bub_sort(str1_c,LEN1); bub_sort(str2_c,LEN2);

  return compare(str1_c,str2_c);
}

void bub_sort(char* a, int len)
{
  char temp;
  for(int i = 0; i < len-1; i++)
    {
      for(int j = 0; j < len-1; j++)
        {
          if(toupper(a[j]) > toupper(a[j+1]))
            {
              temp = a[j];
              a[j] = a[j+1]; a[j+1] = temp;
            }
        }
    }
}
