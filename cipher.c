#include "cipher.h"
#include <string.h>

#define ALPHABET_LEN 26


// See full documentation in header file
void encode (char s[], int k)
{
  for (size_t i = 0; i < strlen(s); i++)
  {
      if (s[i] <= 'z' && s[i] >='a')
      {
          s[i] = (char)(((s[i] - 'a' + k) % ALPHABET_LEN
                  + ALPHABET_LEN) % ALPHABET_LEN + 'a');
      }
      if (s[i] <= 'Z' && s[i] >='A')
      {
          s[i] = (char)(((s[i] - 'A' + k) % ALPHABET_LEN
                  + ALPHABET_LEN) % ALPHABET_LEN + 'A');
      }
  }
}

// See full documentation in header file
void decode (char s[], int k)
{
    encode(s, -k);
}
