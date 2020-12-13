#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COUNT 1024
#define FIRST 100
#define LAST 1000

int row(char *s)
{
	int low = 0;
	int high = 128;
	for (char *p = s; *p && *p != 'R' && *p != 'L'; p++) {
		if (*p == 'F') {
			high -= 2 << (5 - (p - s));
		} else if (*p == 'B') {
			low += 2 << (5 - (p - s));
		}
	}
	return low;
}

int col(char *s)
{
	int low = 0;
	int high = 8;
	for (char *p = s + 7; *(p + 1); p++) {
		if (*p == 'L') {
			high -= 2 << (1 - (p - (s + 7)));
		} else if (*p == 'R') {
			low += 2 << (1 - (p - (s + 7)));
		}
	}
	if (*(s + 9) == 'R')
		return high - 1;
	else if (*(s + 9) == 'L')
		return low;
	else
		return 0;
}

int compare(const void *a, const void *b)
{
	int int_a = *((int *)a);
	int int_b = *((int *)b);

	if (int_a == int_b)
		return 0;
	else if (int_a < int_b)
		return -1;
	else
		return 1;
}

static int ids[COUNT] = { 0 };

int part_one(FILE *fp)
{
	int res = 0;

	char *line = NULL;
	size_t len = 0;
	int i = 0;
	while (getline(&line, &len, fp) != -1) {
		int id = row(line) * 8 + col(line);
		if (id > res)
			res = id;

		ids[i] = id;
		i++;
	}

	return res;
}

int part_two()
{
	int res = 0;

	qsort(ids, COUNT, sizeof(int), compare);

	for (int i = 1; i < COUNT - 1; ++i) {
		if (ids[i] == 0)
			continue;

		if (ids[i] != ids[i + 1] && ids[i] != ids[i - 1] && i > FIRST && i < LAST)
			res = ids[i];
	}

	return res;
}

int main(int argc, char *argv[])
{
	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	clock_t tic = clock();
	printf("%d\n", part_one(fp));
	printf("%d\n", part_two());
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
