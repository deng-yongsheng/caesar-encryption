#ifndef __CAESAR_H
#define __CAESAR_H


void encrypt_text(unsigned char *src, unsigned char *dst, int key);
void decrypt_text(unsigned char *src, unsigned char *dst, int key);

#endif