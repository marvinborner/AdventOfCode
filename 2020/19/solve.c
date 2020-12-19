#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char rules[256][64] = { 0 };

int check_rule(char *inp, char *rule, int index)
{
	char ch;
	int num1, num2, num3, num4;
	if (sscanf(rule, "%d %d | %d %d", &num1, &num2, &num3, &num4) == 4) {
		return (check_rule(inp, rules[num1], index) &&
			check_rule(inp, rules[num2], index + 1)) ||
		       (check_rule(inp, rules[num3], index) &&
			check_rule(inp, rules[num4], index + 1));
	} else if (sscanf(rule, "%d %d", &num1, &num2) == 2) {
		return check_rule(inp, rules[num1], index) &&
		       check_rule(inp, rules[num2], index + 1);
	} else if (sscanf(rule, "\"%c\"", &ch) == 1) {
		return ch == inp[index];
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
			if (check_rule(line, rules[0], 0))
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
