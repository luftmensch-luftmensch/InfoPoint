CC = gcc # Default Compiler

# Per una lista più ampia https://developers.redhat.com/blog/2018/03/21/compiler-and-linker-flags-gcc
CFLAGS = -Wall -Werror -O2 -g -fstack-clash-protection -fstack-protector-all -Wshadow -ftrapv # Gestito per il controllo di overflow

CFLAGS_WITH_THREADS = -pthread $(CFLAGS) # Flag necessaria per i sorgenti che fanno uso dei thread (L'opzione va esplicitata)

LDLIBS = -lm # Linker flags

EXTERNAL_LIBRARY = 

TARGET = server # Executable name result
#SRC = $(wildcard *.c) # Compile all file matching the regex (only *.c files)
SRC = $(wildcard src/*.c) src/utils/common/utils.c

all: $(TARGET)
	@printf "\e[32m%b\e[0m" "Creazione del file completata\n"

# $@ stands for target (left side of :)
# $^ stand for "all element on the right side of :" (in this case $(SRC))
$(TARGET) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $(LDLIBS) $^

.PHONY: clean all # Check for a file named clean

clean:
	rm -f $(TARGET)
