#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

long add_or_mul(long *res, long num, int mul)
{
	if (mul == 0)
		*res += num;
	else
		*res *= num;
	return *res;
}

long evil(char *str, int prec)
{
	long res = 0;
	int mul = 0, skip = 0, brace_cnt = 0;
	for (char *p = str; *p; p++) {
		if (skip) {
			if (*p == '(') {
				brace_cnt++;
			} else if (*p == ')' && !(brace_cnt--)) {
				brace_cnt = 0;
				skip = 0;
			}
			continue;
		}

		if (*p == ' ') {
			continue;
		} else if (*p == '(') {
			add_or_mul(&res, evil(p + 1, prec), mul);
			skip = 1;
		} else if (*p == ')') {
			break; // That's why I don't use switch..case
		} else if (*p == '*') {
			if (prec)
				return add_or_mul(&res, evil(p + 1, prec), 1);
			mul = 1;
		} else if (*p == '+') {
			mul = 0;
		} else if (isdigit(*p)) {
			add_or_mul(&res, *p - '0', mul);
		}
	}
	return res;
}

long part_one(FILE *fp)
{
	long res = 0;

	char *line = NULL;
	size_t len;
	while (getline(&line, &len, fp) != -1)
		res += evil(line, 0);

	return res;
}

long part_two(FILE *fp)
{
	long res = 0;

	char *line = NULL;
	size_t len;
	while (getline(&line, &len, fp) != -1)
		res += evil(line, 1);

	return res;
}

int main(int argc, char *argv[])
{
	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	clock_t tic = clock();
	printf("%lu\n", part_one(fp));
	rewind(fp);
	printf("%lu\n", part_two(fp));
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
