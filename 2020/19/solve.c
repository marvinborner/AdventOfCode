#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char rules[256][256] = { 0 };

static int ind = 0;
int verify(char *inp, char *rule)
{
	//printf("%d: %s\n", ind, rule);
	char ch;
	int num1, num2, num3, num4;
	if (sscanf(rule, "%d %d | %d %d", &num1, &num2, &num3, &num4) == 4) {
		int i = ind;
		if ((verify(inp, rules[num1]) && verify(inp, rules[num2])) ||
		    ((ind = i) && verify(inp, rules[num3]) && verify(inp, rules[num4])))
			return ind;
		else {
			ind = i;
			return 0;
		}
	} else if (sscanf(rule, "%d", &num1) == 1) {
		int i = ind;
		if (verify(inp, rules[num1])) {
			return ind;
		} else {
			ind = i;
			return 0;
		}
	} else if (sscanf(rule, "%d %d", &num1, &num2) == 2) {
		int i = ind;
		if (verify(inp, rules[num1]) && verify(inp, rules[num2])) {
			return ind;
		} else {
			ind = i;
			return 0;
		}
	} else if (sscanf(rule, "\"%c\"", &ch) == 1) {
		/* printf("%c %c\n", ch, inp[ind]); */
		return ch == inp[ind] ? ++ind : 0;
	} else {
		printf("PANIC: %s, %s\n", inp, rule);
		exit(0);
	}

	return 0;
}

long part_one(FILE *fp)
{
	long res = 0;

	int paragraph = 0;
	char *line = NULL;
	size_t len;
	while (getline(&line, &len, fp) != -1) {
		if (line[0] == '\n') {
			paragraph++;
			continue;
		}

		if (paragraph == 0) {
			char rule[64] = { 0 };
			int ind = 0;
			sscanf(line, "%d: %64[0-9a-z \"|]", &ind, rule);
			strcpy(rules[ind], rule);
		} else if (paragraph == 1) {
			ind = 0;
			if (verify(line, rules[0]) == strlen(line) - 1)
				res++;
		}
	}

	return res;
}

long part_two(FILE *fp)
{
	long res = 0;

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
