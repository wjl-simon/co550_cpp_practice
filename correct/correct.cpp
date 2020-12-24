#include <iostream>
//#include <cstring>
#include "correct.h"
#include <cmath>

using namespace std;

/* You are supplied with two helper functions */

/* converts a character into a binary string representation */
void ascii_to_binary(char ch, char *binary);

/* converts a binary string representation into a character */
char binary_to_ascii(const char *binary);

void ascii_to_binary(char ch, char *binary) {
  for (int n = 128; n; n >>= 1) 
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

char binary_to_ascii(const char *binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}


/* now add your own functions here */



// Q1
#define BYTE_LEN 8

void text_to_binary(const char* text, char* binary, int pos)
{
  char temp[BYTE_LEN+1];
  /*
  for(int i = 0; text[i]!='\0'; i++)
    {
      ascii_to_binary(text[i],temp);
      // append temp to the end of binary
      strcpy(binary+i*BYTE_LEN,temp);
    }
  */

  // base case
  if(*text == '\0') return;

  //nomarl case
  ascii_to_binary(*text,temp);
  strcpy(binary+pos*BYTE_LEN,temp); // append temp to the end of binary
  text_to_binary(text+1,binary,pos+1);
}
  
void binary_to_text(const char* binary, char* str)
{
  char temp[BYTE_LEN+1]; int pos = 0;
  for(int i = 0; binary[i]!='\0'; i += BYTE_LEN)
    {
      // extract a byte
      for(int j = 0; j <= BYTE_LEN; j++)
        {
          if(j < BYTE_LEN)
            temp[j] = binary[i+j];
          else
            temp[j] = '\0';
        }
      
      str[pos++] = binary_to_ascii(temp);
    }
  
  str[pos] = '\0';
}


// Q2
#define CW_LEN 7
#define DATA_UNIT 4
void add_error_correction(const char* data, char* corrected)
{
  const int LEN = strlen(data);

  for(int i = 0; i < LEN / DATA_UNIT; i++)
    {
      corrected[0+i*CW_LEN] =
        parity(data[0+i*DATA_UNIT],data[1+i*DATA_UNIT],data[3+i*DATA_UNIT]);

      corrected[1+i*CW_LEN] =
        parity(data[0+i*DATA_UNIT],data[2+i*DATA_UNIT],data[3+i*DATA_UNIT]);

      corrected[2+i*CW_LEN] = data[0+i*DATA_UNIT];

      corrected[3+i*CW_LEN] =
        parity(data[1+i*DATA_UNIT],data[2+i*DATA_UNIT],data[3+i*DATA_UNIT]);

      corrected[4+i*CW_LEN] = data[1+i*DATA_UNIT];
      corrected[5+i*CW_LEN] = data[2+i*DATA_UNIT];
      corrected[6+i*CW_LEN] = data[3+i*DATA_UNIT];
    }
  
  corrected[CW_LEN * (LEN/DATA_UNIT)] = '\0';
}

char parity(char d1, char d2, char d3)
{
  return (d1+d2+d3) %2 == 0 ? '0' : '1';
}



// Q3
int decode(const char* received, char* decoded)
{
  char rx_part[CW_LEN+1]; // one codeword

  int num_err = 0;
  int count_word = 0;
  for(int i = 0; received[i]!='\0'; i+=CW_LEN, count_word++)
    {
      // extract one codeword
      for(int j = 0; j <= CW_LEN; j++)
        {
          if(j < CW_LEN)
            rx_part[j] = received[j+i];
          else
            rx_part[j] = '\0';
        }
      
      //decode one word
      if(decode_1_cw(rx_part, decoded+count_word*DATA_UNIT))
        num_err++;
    }

  return num_err;
}

bool decode_1_cw(char* codeword, char* data)
{ 
  char p[4]; // parity check bits
  p[0] = parity(codeword[3], codeword[4], codeword[5], codeword[6]);
  p[1] = parity(codeword[1], codeword[2], codeword[5], codeword[6]);
  p[2] = parity(codeword[0], codeword[2], codeword[4], codeword[6]);
  p[3] = '\0';
  
  // see at which pos there is an error
  int pos = bin_to_dec(p);

  // correcting bits
  if(pos == 0)
    {
      // extract the bits in the codeword to data
      data[0] = codeword[2];
      data[1] = codeword[4];
      data[2] = codeword[5];
      data[3] = codeword[6];
      data[4] = '\0';
      
      return false; // no error!
    }
  else // have error in the codeword, filp the bit
    {
      // correct the bit
      codeword[pos-1] = (codeword[pos-1]=='1' ? '0' : '1');

      // extract the bits in the codeword to data
      data[0] = codeword[2];
      data[1] = codeword[4];
      data[2] = codeword[5];
      data[3] = codeword[6];
      data[4] = '\0';
      return true;
    }
}

char parity(char b1, char b2, char b3, char b4)
{
  return (b1+b2+b3+b4) % 2 == 0 ? '0' : '1';
}

int bin_to_dec(const char* bin)
{
  const int LEN = strlen(bin);

  // base case
  if(LEN == 0) return 0;

  return (*bin-'0') * pow(2,LEN-1) + bin_to_dec(bin+1);
}
