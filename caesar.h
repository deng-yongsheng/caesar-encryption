#ifndef __CAESAR_H
#define __CAESAR_H

#define MAX_PASSOWRD_LEN 10

#define Write_OK 2
#define Read_OK 4
#define Exist_OK 0
/**
 * @brief 导出的默认文件后缀
 *
 */
#define default_output_filename_suffix ".caesar"

extern int get_password();
extern void encrypt_text(const char *src, char *dst, int key);
extern void decrypt_text(const char *src, char *dst, int key);
extern void encrypt_file(const char *src_filename, const char *dst_filename, int key);
extern void decrypt_file(const char *src_filename, const char *dst_filename, int key);

#endif