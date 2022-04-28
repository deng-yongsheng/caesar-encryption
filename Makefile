CC = gcc

.PHONY : clean run

main.exe : main.c caesar.c
	$(CC) $^ -o $@ -fexec-charset=gbk

run : main.exe
	./main.exe

clean:
	rm *.o
	rm *.exe
