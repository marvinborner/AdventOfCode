DEBUG = -Wno-error -Og -ggdb3 -s -fsanitize=undefined -fsanitize=address -fstack-protector-all
CFLAGS = -Wall -Wextra -Werror -Wshadow -Wpointer-arith -Wwrite-strings -Wredundant-decls -Wnested-externs -Wformat=2 -Wmissing-declarations -Wstrict-prototypes -Wmissing-prototypes -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wundef -Wold-style-definition -Wvla -pedantic-errors -Ofast

# Not the best makefile but idc

debug:
	@gcc $(CFLAGS) $(DEBUG) solve.c -o solve.o

build:
	@gcc $(CFLAGS) solve.c -o solve.o

clean:
	@rm -f *.o

run: debug
	@./solve.o

time: build
	@./solve.o
