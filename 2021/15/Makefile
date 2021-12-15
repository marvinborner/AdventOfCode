DEBUG = -Wno-error -Og -g -s -fsanitize=undefined -fsanitize=address -fstack-protector-all
CFLAGS = -Wall -Wextra -Werror -Wshadow -Wpointer-arith -Wwrite-strings -Wredundant-decls -Wnested-externs -Wformat=2 -Wmissing-declarations -Wstrict-prototypes -Wmissing-prototypes -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wundef -Wold-style-definition -Wvla -pedantic -Ofast -std=gnu99

# Not the best makefile but idc

debug:
	@gcc $(CFLAGS) $(DEBUG) solve.c -o solve.o -L/usr/lib -lcrypto

build:
	@gcc $(CFLAGS) solve.c -o solve.o -L/usr/lib -lcrypto

clean:
	@rm -f *.o

run: debug
	@./solve.o

time: build
	@./solve.o
