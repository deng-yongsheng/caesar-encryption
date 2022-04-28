#include <stdio.h>
#include <stdlib.h>
#include "caesar.h"

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

    key = get_password();
    encrypt_text(string, encrypt_str, key);
    printf("加密后的字符串序列：%s\n\n", encrypt_str);

    decrypt_text(encrypt_str, string, key);
    printf("加密后再的字符串序列：%s\n\n", string);

    return 0;
}
