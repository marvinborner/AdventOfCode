#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COUNT(a) ((int)(sizeof(a) / sizeof 0 [a]))

#define FORLINE                                                                                    \
	char *line = NULL;                                                                         \
	size_t len = 0;                                                                            \
	while (getline(&line, &len, fp) != EOF)
#define FREELINE                                                                                   \
	if (line)                                                                                  \
	free(line)

#define IDX(a, b) (((a) - 'A') * 26 + ((b) - 'A'))
#define LEFT(i) (((i) / 26) + 'A')
#define RIGHT(i) (((i) % 26) + 'A')
static void solve(FILE *fp)
{
	char input[32] = { 0 };
	char rules[26 * 26] = { 0 };

	int klaus = 0;
	FORLINE
	{
		if (!klaus)
			strcpy(input, line);
		else if (klaus >= 2)
			rules[IDX(line[0], line[1])] = line[6];
		klaus++;
	}
	FREELINE;

	long pairs[26 * 26] = { 0 };
	long counts[26] = { 0 };

	for (char *p = input; *p && *p != '\n'; p++) {
		if (*(p + 1))
			pairs[IDX(*p, *(p + 1))] += 1;
		counts[*p - 'A'] += 1;
	}

	int start = 0, end = 10;
aah:
	for (int i = start; i < end; i++) {
		long new[26 * 26] = { 0 };
		for (int j = 0; j < COUNT(pairs); j++) {
			char a = LEFT(j), b = RIGHT(j);
			char insert = rules[IDX(a, b)];
			if (insert) {
				new[IDX(a, insert)] += pairs[j];
				new[IDX(insert, b)] += pairs[j];
				counts[insert - 'A'] += pairs[j];
			} else {
				new[j] = pairs[j];
			}
		};

		memcpy(pairs, new, sizeof(pairs));
	}

	long max = 0, min = 0x4242424242424242;
	for (int i = 0; i < COUNT(counts); i++) {
		if (!counts[i])
			continue;

		if (counts[i] > max)
			max = counts[i];
		else if (counts[i] < min)
			min = counts[i];
	}

	printf("%lu\n", max - min);

	if (start == 0) {
		start = end;
		end = 40;
		goto aah;
	}
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	clock_t tic = clock();
	solve(fp);
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
