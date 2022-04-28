#include <conio.h>
#include "caesar.h"

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
 * @brief 获取用户输入的凯撒密码，最大长度为 MAX_PASSOWRD_LEN
 *
 * @return int
 */
int get_password()
{
    unsigned char *passwd = (unsigned char *)malloc(sizeof(unsigned char) * MAX_PASSOWRD_LEN);
    int i, int_passwd = 0;
    while (int_passwd == 0)
    {
        printf("请输入密码：");
        for (i = 0; i < MAX_PASSOWRD_LEN; i++)
        {
            passwd[i] = getch();
            if (passwd[i] == '\n' || passwd[i] == '\r')
            {
                printf("\r\n");
                break;
            }
            else
            {
                printf("*");
            }
        };
        passwd[i] = '\0';
        int_passwd = atoi(passwd);
        if (int_passwd == 0)
        {
            printf("输入的密码无效\n");
        }
    }

    return int_passwd;
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

/**
 * @brief 针对二进制的凯撒加密算法
 * @brief 判断文件权限
 *
 * @param src 源数据
 * @param dst 目标数据
 * @param count 数据长度
 * @param key 密钥
 * @param src_filename 源文件，需要存在且具有读权限
 * @param dst_filename 目标文件，不存在或具有写权限
 * @return int
 */
void encrypt(unsigned char *src, unsigned char *dst, int count, int key)
int verify_permissions(const char *src_filename, const char *dst_filename)
{
    if (access(src_filename, Exist_OK) != 0)
    {
        fprintf(stderr, "\"%s\"文件不存在\n", src_filename);
        return -1;
    }
    if (access(src_filename, Read_OK) != 0)
    {
        fprintf(stderr, "没有对\"%s\"文件的读取权限\n", src_filename);
        return -1;
    }
    // 判断文件是否存在
    if (access(dst_filename, Exist_OK) == 0)
    {
        fprintf(stderr, "\"%s\"文件存在，将进行覆盖\n", dst_filename);
        if (access(dst_filename, Write_OK) != 0)
        {
            fprintf(stderr, "没有对\"%s\"文件的写入权限\n", dst_filename);
            return -1;
        }
    }
    return 0;
}

{
    key = key % 256;
    for (int i = 0; i < count; i++)
    {
    }
}