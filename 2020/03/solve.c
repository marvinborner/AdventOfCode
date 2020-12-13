#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int part_one(FILE *fp)
{
	int res = 0;

	char *line = NULL;
	size_t len = 0, strlen = 0;
	int curr = 0;
	while ((strlen = getline(&line, &len, fp)) != -1) {
		if (line[curr % (strlen - 1)] == '#')
			res++;
		curr += 3;
	}

	return res;
}

#define DOWN_TWO (1 << 15)
int part_two(FILE *fp)
{
	int final = 1;
	int opt[] = { 1, 3, 5, 7, 1 | DOWN_TWO };

	char *line = NULL;
	size_t len = 0, strlen = 0;
	for (int i = 0; i < sizeof(opt) / sizeof(opt[0]); i++) {
		int res = 0, row = 0, curr = 0;
		while ((strlen = getline(&line, &len, fp)) != -1) {
			if (row++ % 2 == 1 && opt[i] & DOWN_TWO)
				continue;
			if (line[curr % (strlen - 1)] == '#')
				res++;
			curr += opt[i] & ~DOWN_TWO;
		}
		rewind(fp);
		final *= res;
	}

	return final;
}

int main(int argc, char *argv[])
{
	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	clock_t tic = clock();
	printf("%d\n", part_one(fp));
	rewind(fp);
	printf("%u\n", part_two(fp));
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
