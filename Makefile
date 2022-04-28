CC = gcc

PRJ = caesar
# 目标平台
# windows or linux
PLATFORM = windows

CFILES = \
	main.c \
	caesar.c

.PHONY : clean run

ifeq ($(PLATFORM), windows)

$(PRJ) : $(CFILES)
	$(CC) $^ -o $@ -fexec-charset=gbk

run : $(PRJ).exe
	./$(PRJ).exe

clean : 
	del /Q *.exe

else

$(PRJ) : $(CFILES)
	$(CC) $^ -o $@

run : $(PRJ)
	./$(PRJ)

clean:
	rm /f *.exe

endif
