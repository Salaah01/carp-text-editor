CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFILES   = $(wildcard *.c)
OBJFILES = $(CFILES:.c=.o)
OUT      = main

$(OUT): $(OBJFILES)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJFILES) $(OUT)
