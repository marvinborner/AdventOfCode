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

#define WHOLE                                                                                      \
	fseek(fp, 0, SEEK_END);                                                                    \
	long fsize = ftell(fp);                                                                    \
	fseek(fp, 0, SEEK_SET);                                                                    \
	char *data = malloc(fsize + 1);                                                            \
	fread(data, 1, fsize, fp);                                                                 \
	data[fsize] = 0;                                                                           \
	data[fsize--] = 0

static int part_one(FILE *fp)
{
	int res = 0xffffffff;

	int prev = 0;
	FORLINE
	{
		int strength = atoi(line);
		if (strength > prev)
			res++;
		prev = strength;
	}
	FREELINE;

	return res;
}

static int part_two(FILE *fp)
{
	int res = 0;

	int prevstrength = -1;

	int prevprev = -1;
	int prev = -1;
	FORLINE
	{
		int orig = atoi(line);
		int strength = 0;
		if (prevprev > 0 && prev > 0)
			strength = orig + prev + prevprev;
		if (prevstrength > 0 && strength > prevstrength)
			res++;
		prevstrength = strength;
		prevprev = prev;
		prev = orig;
	}
	FREELINE;

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
