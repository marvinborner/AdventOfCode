.PHONY: solve.c

solve.o: solve.c
	@gcc -Ofast $+ -o $@ -lm

clean:
	@rm -f *.o

run: solve.o
	@./solve.o
