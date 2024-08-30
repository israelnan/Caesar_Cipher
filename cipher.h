#ifndef CIPHER_H
#define CIPHER_H


/**
 * Encodes the given string according to the given shift value - k.
 * @param s - given string.
 * @param k - given shift value.
 */
void encode (char s[], int k);

/**
 * Decodes the given string according to the given shift value - k.
 * @param s - given string.
 * @param k - given shift value.
 */
void decode (char s[], int k);

#endif //CIPHER_H
