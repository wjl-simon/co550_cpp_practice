#include <cctype>
#include <cstring>
#include "words.h"

using namespace std;

#define MAX_STR_LEN 100

void reverse(const char* str1, char str2[])
{
  const int LEN = strlen(str1);
  
  for(int i = 0; i < LEN; i++)
    str2[LEN - i -1] = str1[i];

  str2[LEN] = '\0';
}


bool compare(const char* str1, const char* str2)
{
  char str_1[MAX_STR_LEN]; char str_2[MAX_STR_LEN];
  strcpy(str_1,str1); strcpy(str_2,str2);

  // eliminating the non letters
  eli_non_alp(str_1);
  eli_non_alp(str_2);

  // starting to compare
  return compare_solver(str_1,str_2);
}

// eliminate the non alphbet letters
void eli_non_alp(char str[])
{
  if(*str == '\0') return; // base case
    
  if(isalpha(*str) == 0) // not a alpha ('\0' doesn't count)
    {
      for(int i = 0; str[i]!='\0'; i++)
        str[i] = str[i+1]; // the '\0' is already copied!

      eli_non_alp(str);
    }
  else
    eli_non_alp(++str);
  

}

bool compare_solver(char* str1, char* str2)
{

  if(*str1 == '\0' || *str2 == '\0') return true;
  
  if(toupper(*str1) == toupper(*str2))
    {
      if(compare_solver(str1+1,str2+1))
        return true;
      else
        return false;
    }
  else
    return false;
}

bool palindrome(const char* sentence)
{
  char str[MAX_STR_LEN]; strcpy(str, sentence);
  
  // eliminate the non alphabet
  eli_non_alp(str);
  const int LEN = strlen(str);

  for(int i = 0; i < LEN/2; i++)
    {
      if(toupper(str[i]) != toupper(str[LEN-1-i]))
        return false;
    }

  return true;
}

void alp_sort(char str[])
{
  const int LEN = strlen(str);

  int cur_min_idx = 0;
  
  for(int i = 0; i < LEN; i++)
    {
      cur_min_idx = i;
      // get the idx of the min (from pos [i] to end)
      for(int j = i; j < LEN; j++)
        {
          if(toupper(str[j]) <= toupper(str[cur_min_idx]))
            cur_min_idx = j;
        }
      // swap the min and str[i]
      swap(cur_min_idx,i,str);
    }
}

void swap(int a, int b, char str[])
{
  char temp = str[a];
  str[a] = str[b];
  str[b] = temp;
}

bool anagram(const char* str1, const char* str2)
{
  char str_1[MAX_STR_LEN]; strcpy(str_1, str1);
  char str_2[MAX_STR_LEN]; strcpy(str_2, str2);
  // eliminate the non alphabet
  eli_non_alp(str_1); eli_non_alp(str_2);

  // sort the two strings
  alp_sort(str_1);
  alp_sort(str_2);

  // compare
  return compare(str_1,str_2);
}
