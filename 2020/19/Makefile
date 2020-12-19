.PHONY: solve.c

solve.o: solve.c
	@gcc -Ofast $+ -o $@

clean:
	@rm -f *.o

run:
	@node solve.js

c: solve.o
	@./solve.o
