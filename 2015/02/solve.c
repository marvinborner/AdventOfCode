#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int part_one(FILE *fp)
{
	int res = 0;

	char *line = NULL;
	size_t len = 0;
	while (getline(&line, &len, fp) != EOF) {
		int w, l, h;
		sscanf(line, "%dx%dx%d", &w, &l, &h);
		res += 2 * l * w + 2 * w * h + 2 * h * l;

		int a = w * l, b = l * h, c = w * h;
		res += (a <= b && a <= c) ? a : (b <= c && b <= a) ? b : (c <= a && c <= b) ? c : 0;
	}

	if (line)
		free(line);

	return res;
}

static int part_two(FILE *fp)
{
	int res = 0;

	char *line = NULL;
	size_t len = 0;
	while (getline(&line, &len, fp) != EOF) {
		int w, l, h;
		sscanf(line, "%dx%dx%d", &w, &l, &h);

		int a = 2 * w + 2 * l, b = 2 * l + 2 * h, c = 2 * w + 2 * h;
		res += (a <= b && a <= c) ? a : (b <= c && b <= a) ? b : (c <= a && c <= b) ? c : 0;
		res += w * h * l;
	}

	if (line)
		free(line);

	return res;
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

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
