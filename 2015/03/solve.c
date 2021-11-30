#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FORLINE                                                                                    \
	char *line = NULL;                                                                         \
	size_t len = 0;                                                                            \
	while (getline(&line, &len, fp) != EOF)
#define FREELINE                                                                                   \
	if (line)                                                                                  \
	free(line)

#define FORCH                                                                                      \
	char ch = 0;                                                                               \
	while ((ch = fgetc(fp)) != EOF)

#define INFINITE 1024
static int part_one(FILE *fp)
{
	int res = 1;
	char houses[INFINITE * 2][INFINITE * 2] = { 0 };
	int x = INFINITE, y = INFINITE;

	houses[x][y] = 1;
	FORCH
	{
		if (ch == '>')
			x++;
		else if (ch == '<')
			x--;
		else if (ch == '^')
			y++;
		else if (ch == 'v')
			y--;

		if (!houses[x][y]) {
			houses[x][y] = 1;
			res++;
		}
	}

	return res;
}

static int part_two(FILE *fp)
{
	int res = 1;

	char houses[INFINITE * 2][INFINITE * 2] = { 0 };
	int rx = INFINITE, ry = INFINITE, sx = INFINITE, sy = INFINITE;

	houses[sx][sy] = 1;
	int robo = 0;
	FORCH
	{
		int *x = robo ? &rx : &sx;
		int *y = robo ? &ry : &sy;

		if (ch == '>')
			(*x)++;
		else if (ch == '<')
			(*x)--;
		else if (ch == '^')
			(*y)++;
		else if (ch == 'v')
			(*y)--;

		if (!houses[*x][*y]) {
			houses[*x][*y] = 1;
			res++;
		}

		robo = !robo;
	}

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
