.PHONY: solve.c

solve.o: solve.c
	@gcc -g -Ofast $+ -o $@

clean:
	@rm -f *.o

run: solve.o
	@./solve.o
