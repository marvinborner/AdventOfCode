#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	int depth = 0, horizontal = 0;
	FORLINE
	{
		char command[32] = { 0 };
		int amount;
		sscanf(line, "%s %d", command, &amount);
		if (!strcmp(command, "forward"))
			horizontal += amount;
		else if (!strcmp(command, "down"))
			depth += amount;
		else if (!strcmp(command, "up"))
			depth -= amount;
	}
	FREELINE;

	return depth * horizontal;
}

static int part_two(FILE *fp)
{
	int aim = 0, depth = 0, horizontal = 0;
	FORLINE
	{
		char command[32] = { 0 };
		int amount;
		sscanf(line, "%s %d", command, &amount);
		if (!strcmp(command, "forward")) {
			horizontal += amount;
			depth += aim * amount;
		} else if (!strcmp(command, "down")) {
			aim += amount;
		} else if (!strcmp(command, "up")) {
			aim -= amount;
		}
	}
	FREELINE;

	return depth * horizontal;
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
