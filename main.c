#include <stdio.h>
#include <conio.h>

/**
 * @brief 针对二进制的凯撒加密算法
 *
 * @param src 源数据
 * @param dst 目标数据
 * @param count 数据长度
 * @param key 密钥
 */
void encrypt(unsigned char *src, unsigned char *dst, int count, int key)
{
    key = key % 256;
    for (int i = 0; i < count; i++)
    {
    }
}
/**
 * @brief 自定义字符集
 *
 */
unsigned char character_set[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
/**
 * @brief 自定义字符集的长度
 *
 */
int CHARSET_LENGTH = sizeof(character_set) - 1;

/**
 * @brief 获取某个字符的内部编码
 *
 * @param ch 字符
 * @return 内部编码，如果不含此字符，则返回 -1
 */
int get_char_code(unsigned char ch)
{
    for (int i = 0; character_set[i] != '\0'; i++)
    {
        if (character_set[i] == ch)
        {
            return i;
        }
    }
    return -1;
}

/**
 * @brief 加密普通文本
 *
 * @param src 源字符串
 * @param dst 目标保存位置
 * @param key 密钥，最大值为 CHARSET_LENGTH-1
 */
void encrypt_text(unsigned char *src, unsigned char *dst, int key)
{
    int i;
    key = key % CHARSET_LENGTH;
    for (i = 0; src[i] != '\0'; i++)
    {
        int code = get_char_code(src[i]);
        if (code != -1)
        {
            dst[i] = character_set[(code + key) % CHARSET_LENGTH];
        }
        else
        {
            dst[i] = src[i];
        }
    }
    dst[i] = '\0';
}

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
