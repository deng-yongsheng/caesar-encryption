#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "caesar.h"

#define MAX_PASSOWRD 10

/**
 * @brief 解密普通文本
 *
 * @param src 密码字符串
 * @param dst 目标保存位置
 * @param key 密钥，最大值为 CHARSET_LENGTH-1
 */
void decrypt_text(unsigned char *src, unsigned char *dst, int key)
{
    int i;
    key = key % CHARSET_LENGTH;
    for (i = 0; src[i] != '\0'; i++)
    {
        int code = get_char_code(src[i]);
        if (code != -1)
        {
            dst[i] = character_set[(code - key) % CHARSET_LENGTH];
        }
        else
        {
            src[i] = dst[i];
        }
    }
    dst[i] = '\0';
}

int main(int argc, char const *argv[])
{
    char string[200];
    char encrypt_str[200];
    int key = 0;
    for (int i = 0; i < argc; i++)
    {
        printf("参数%d：%s\n", i, argv[i]);
    }

    printf("请输入要加密的字符序列：");
    scanf("%s", string);
    printf("\n");

    printf("请输入密码：");
    scanf("%d", &key);
    printf("\n");

    encrypt_text(string, encrypt_str, key);
    printf("加密后的字符串序列：%s\n\n", encrypt_str);

    decrypt_text(encrypt_str, string, key);
    printf("加密后再的字符串序列：%s\n\n", string);

    return 0;
}
