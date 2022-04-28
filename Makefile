CC = gcc

.PHONY : clean run

CFILES = \
	main.c \
	caesar.c

main.exe : $(CFILES)
	$(CC) $^ -o $@ -fexec-charset=gbk

run : main.exe
	./main.exe

clean: 
	rm *.exe
