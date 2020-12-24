#include "substring.h"
#include <cstring>

// iterative version
/*
bool is_prefix(const char* str1, const char* str2)
{
  for(int i = 0; str1[i]!='\0'; i++)
    {
      if(str1[i] != str2[i])
        return false;
    }

  return true;
}
*/

// recursive version
bool is_prefix(const char* str1, const char* str2)
{
  // base case
  if(*str1 == '\0') return true;
  
  if(*str1 == *str2)
  {
    if(is_prefix(str1+1,str2+1))
      return true;
    else
      return false;
  }
  else return false;

}


int substring_position(const char* str1, const char* str2, int count)
{
  // base case 1
  if(*str2 == '\0' && *str1 != '\0') return -1;

  // base case 2
  if(*str1 == '\0') return 0;

  // base case 3
  if(is_prefix(str1, str2)) return count;
  else // recursion
    return substring_position(str1, str2+1,++count);
}


int substring_position2(const char* str1, const char* str2)
{
  return strstr(str2,str1)? strstr(str2,str1) - str2 : -1; 
}
