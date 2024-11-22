CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g
SRC = strace_tool.c

strace_tool: $(SRC)
		$(CC) $(CFLAGS) $(SRC) -o strace_tool

run: strace_tool
	strace -f -o strace_log.txt ./strace_tool

clean:
	rm -f strace_tool strace_log.txt

.PHONY: clean