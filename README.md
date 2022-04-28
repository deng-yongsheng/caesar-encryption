# 凯撒加密-C语言实现

### 依赖

+ gcc
+ cmake

### windows 平台下编译

```shell
make PLATFORM=windows
```

### Linux 平台编译

```shell
make PLATFORM=linux
```

### 使用

+ 交互式加密解密

```shell
./caesar
```

+ 对指定文件进行加密
  
  对 `[filename]`加密 ，输出文件到 `[filename].caesar`

```shell
./caesar [filename]
```

+ 对文件进行加密
  
  对后缀名为`[filename].caesar`的文件进行解密，输出文件到`[filename]`

```shell
./caesar [filename].caesar
```
