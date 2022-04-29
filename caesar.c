#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
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
 * @brief 从控制台获取用户输入的凯撒密码，最大值为 MAX_PASSOWRD_LEN
 *
 * @return int
 */
int get_password()
{
    char passwd[MAX_PASSOWRD_LEN + 1];
    int int_passwd = 0;
    while (int_passwd == 0)
    {
        printf("请输入密码：");
        for (int i = 0; i < MAX_PASSOWRD_LEN; i++)
        {
            passwd[i] = getch();
            if (passwd[i] == '\n' || passwd[i] == '\r')
            {
                printf("\r\n");
                // 末尾添加结束符
                passwd[i + 1] = '\0';
                break;
            }
            else
            {
                printf("*");
            }
        };
        int_passwd = atoi(passwd);
        if (int_passwd == 0)
        {
            fprintf(stderr, "输入的密码无效\n");
        }
    }

    return int_passwd;
}

/**
 * @brief 获取文件尺寸
 *
 * @param filename
 * @return int
 */
int get_file_size(const char *filename)
{
    struct stat buf;
    int fd = open(filename, _O_RDONLY);

    if (stat(filename, &buf) > -1)
    {
        close(fd);
        printf("%s 文件的尺寸为: %d\n", filename, buf.st_size);
        return buf.st_size;
    }
    else
    {
        close(fd);
        fprintf(stderr, "错误：%s\n", strerror(errno));
        return -1;
    }
}

/**
 * @brief 加密普通文本
 *
 * @param src 源字符串
 * @param dst 目标保存位置
 * @param key 口令，最大值为 CHARSET_LENGTH-1
 */
void encrypt_text(const char *src, char *dst, int key)
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
 * @param key 口令，最大值为 CHARSET_LENGTH-1
 */
void decrypt_text(const char *src, char *dst, int key)
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
            dst[i] = src[i];
        }
    }
    dst[i] = '\0';
}

/**
 * @brief 判断文件权限
 *
 * @param src_filename 源文件，需要存在且具有读权限
 * @param dst_filename 目标文件，不存在或具有写权限
 * @return int
 */
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

/**
 * @brief 对文件进行凯撒加密
 *
 * @param src_filename 源文件名，需要存在且具有读权限
 * @param dst_filename 目标文件名，不存在或具有写权限
 * @param key 口令
 */
void encrypt_file(const char *src_filename, const char *dst_filename, int key)
{
    key = key % 256;
    if (verify_permissions(src_filename, dst_filename) == 0)
    {
        // 打开源文件
        FILE *src_file = fopen(src_filename, "r");
        // 读取并对文件进行加密
        // 获取文件尺寸
        fseek(src_file, 0, SEEK_END);
        int src_file_size = ftell(src_file);
        // 开辟内存
        unsigned char *text = (unsigned char *)malloc(src_file_size + 1);
        rewind(src_file);
        fread(text, sizeof(unsigned char), src_file_size, src_file);
        // 关闭源文件
        fclose(src_file);
        // 加密
        for (int i = 0; i < src_file_size; i++)
        {
            text[i] = (text[i] + key) % 256;
        }
        // 输出到源文件
        FILE *dst_file = fopen(dst_filename, "w");
        fwrite(text, sizeof(unsigned char), src_file_size, dst_file);
        free(text);
        // 关闭目标文件
        fclose(dst_file);
        printf("加密完成！");
    }
}
/**
 * @brief 对文件进行凯撒加密解密
 *
 * @param src_filename 源文件名，需要存在且具有读权限
 * @param dst_filename 目标文件名，不存在或具有写权限
 * @param key 口令
 */
void decrypt_file(const char *src_filename, const char *dst_filename, int key)
{
    key = key % 256;
    if (verify_permissions(src_filename, dst_filename) == 0)
    {
        // 打开源文件
        FILE *src_file = fopen(src_filename, "r");
        // 读取并对文件进行加密
        // 获取文件尺寸
        fseek(src_file, 0, SEEK_END);
        int src_file_size = ftell(src_file);
        // 开辟内存
        unsigned char *text = (unsigned char *)malloc(src_file_size + 1);
        rewind(src_file);
        fread(text, sizeof(unsigned char), src_file_size, src_file);
        // 关闭源文件
        fclose(src_file);
        // 解密
        for (int i = 0; i < src_file_size; i++)
        {
            text[i] = (text[i] - key) % 256;
        }
        // 输出到源文件
        FILE *dst_file = fopen(dst_filename, "w");
        fwrite(text, sizeof(unsigned char), src_file_size, dst_file);
        free(text);
        // 关闭目标文件
        fclose(dst_file);
        printf("解密完成！");
    }
}