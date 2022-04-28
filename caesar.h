#ifndef __CAESAR_H
#define __CAESAR_H

#define MAX_PASSOWRD_LEN 10

void encrypt_text(unsigned char *src, unsigned char *dst, int key);
void decrypt_text(unsigned char *src, unsigned char *dst, int key);

#endif