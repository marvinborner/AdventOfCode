#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int part_one(FILE *fp)
{
	int res = 0;

	char *line = NULL;
	size_t len = 0;

	int current = 0;
	while (getline(&line, &len, fp) != -1) {
		if (line[0] == '\n') {
			if (current > res)
				res = current;
			current = 0;
			continue;
		}

		int num;
		sscanf(line, "%d\n", &num);
		current += num;
	}

	if (line)
		free(line);

	return res;
}

static int sum(int maxes[3])
{
	int s = 0;
	for (int i = 0; i < 3; i++)
		s += maxes[i];
	return s;
}

static void replace_min(int maxes[3], int replace)
{
	int s = 0;
	for (int i = 0; i < 3; i++)
		if (maxes[i] < maxes[s])
			s = i;
	if (replace > maxes[s])
		maxes[s] = replace;
}

static int part_two(FILE *fp)
{
	char *line = NULL;
	size_t len = 0;

	int maxes[3] = { 0 };

	int current = 0;
	while (getline(&line, &len, fp) != -1) {
		if (line[0] == '\n') {
			replace_min(maxes, current);
			current = 0;
			continue;
		}

		int num;
		sscanf(line, "%d\n", &num);
		current += num;
	}
	replace_min(maxes, current);

	if (line)
		free(line);

	return sum(maxes);
}

int main(void)
{
	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	clock_t tic = clock();
	printf("%d\n", part_one(fp));
	rewind(fp);
	printf("%d\n", part_two(fp));
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
