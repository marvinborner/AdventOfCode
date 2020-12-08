.PHONY: solve.c

solve.o: solve.c
	@gcc $+ -o $@ -lm

clean:
	@rm -f *.o

run: solve.o
	@./solve.o
