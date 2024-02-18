CFLAGS = -Wall -Wextra -std=c99 -pedantic -g3
#-Werror

all: options lc3

options:
	@echo lc3 build options:
	@echo "CFLAGS	= $(CFLAGS)"
	@echo "CC	= $(CC)"

%.o: %.c
	$(CC) -c $(CFLAGS) $<

lc3: lc3.o
	$(CC) -o $@ $^ $(LIBS) -fsanitize=address -fsanitize=undefined

clean:
	rm -f lc3
	rm -f *.o

.PHONY: all options clean
