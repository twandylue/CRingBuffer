CFLAGS=-Wall -Wextra -Werror -std=c11 -pedantic -ggdb
STYLE=llvm # google, llvm, chromium, mozilla, webkit

ringbuffer: main.c
	cc $(CFLAGS) main.c -o rb

format:
	clang-format --style=$(STYLE) -i *.c

clean:
	rm -f rb
