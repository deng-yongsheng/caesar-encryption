#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include <conio.h>
#include "caesar.h"

int main(int argc, char const *argv[])
{
    char string[200];
    char encrypt_str[200];
    int key = 0;
    // 判断参数个数，如果参数数量超过1，则判断文件是否存在，对文件进行加密
    if (argc > 1)
    {
        // 导出的文件名后缀的长度
        int suffix_length = strlen(default_output_filename_suffix);
        for (int f = 1; f < argc; f++)
        {
            const char *src_filename = argv[f];
            // 生成默认的输出文件名
            char output_filename[100] = "";
            char default_output_filename[100] = "";
            // 源文件名
            int src_filename_length = strlen(src_filename);
            // 判断输入文件名是否以 .caesar 结尾
            if (src_filename_length > suffix_length && strcmp(src_filename + src_filename_length - suffix_length, default_output_filename_suffix) == 0)
            {
                // 进行解密操作
                printf("解密文件 \"%s\"\n", src_filename);
                // 获取用户输入密码
                key = get_password();
                // 生成默认的输出文件名
                strcpy(default_output_filename, src_filename);
                // 删除导出文件名后缀
                default_output_filename[src_filename_length - suffix_length] = '\0';
                // 用户输出文件名
                printf("请输入输出文件名(default: %s): ", default_output_filename);
                gets(output_filename);
                if (strlen(output_filename) == 0)
                {
                    strcpy(output_filename, default_output_filename);
                }
                // 对文件执行加密操作
                decrypt_file(src_filename, output_filename, key);
            }
            else
            {
                // 进行加密操作
                printf("加密文件 \"%s\"\n", src_filename);
                // 获取用户输入密码
                key = get_password();
                // 生成默认的输出文件名
                strcpy(default_output_filename, src_filename);
                // 添加导出文件名后缀
                strcat(default_output_filename, default_output_filename_suffix);
                // 用户输出文件名
                printf("请输入输出文件名(default: %s): ", default_output_filename);
                gets(output_filename);
                if (strlen(output_filename) == 0)
                {
                    strcpy(output_filename, default_output_filename);
                }
                // 对文件执行加密操作
                encrypt_file(src_filename, output_filename, key);
            }
        }
    }
    else
    {
        while (1)
        {
            char action = ' ';
            while (1)
            {
                if (action == 'e' || action == 'd')
                {
                    break;
                }
                else if (action == '\3')
                {
                    printf("\nCtrl+C 程序结束\n");
                    exit(0);
                }
                printf("按e进行加密，d进行解密：", action, action);
                action = getch();
                printf("\r\n");
            }
            if (action == 'e')
            {
                // 从控制台获取明文
                printf("请输入要加密的明文：");
                scanf("%s", string);
                printf("\n");
                key = get_password();
                encrypt_text(string, encrypt_str, key);
                printf("密文：%s\n\n", encrypt_str);
            }
            else if (action == 'd')
            {
                // 从控制台获取密文
                printf("请输入要解密的密文：");
                scanf("%s", string);
                printf("\n");
                key = get_password();
                decrypt_text(string, encrypt_str, key);
                printf("明文：%s\n\n", encrypt_str);
            }
        }
    }
    return 0;
}
