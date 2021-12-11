#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ABS(a) ((a) < 0 ? -(a) : (a))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define COUNT(a) ((int)(sizeof(a) / sizeof 0 [a]))

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
	fread(data, 1, fsize, fp);

#define SIZE 10
#define LINE (SIZE + 1)
#define BEYOND 42
#define JUSTFLASHED 33
#define INC(x, y)                                                                                  \
	if ((x) >= 0 && (x) < SIZE && (y) >= 0 && (y) < SIZE) {                                    \
		if (data[(y)*LINE + (x)] == '9') {                                                 \
			data[(y)*LINE + (x)] = BEYOND;                                             \
		} else if (data[(y)*LINE + (x)] >= '0') {                                          \
			inc++;                                                                     \
			data[(y)*LINE + (x)]++;                                                    \
		}                                                                                  \
	}

static int flash(char *data, int cnt)
{
	int inc = 0;
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			if (data[y * LINE + x] == BEYOND) {
				cnt++;
				INC(x - 1, y - 1);
				INC(x + 0, y - 1);
				INC(x + 1, y - 1);
				INC(x - 1, y + 0);
				INC(x + 1, y + 0);
				INC(x - 1, y + 1);
				INC(x + 0, y + 1);
				INC(x + 1, y + 1);
				data[y * LINE + x] = JUSTFLASHED;
			}
		}
	}
	if (inc > 0)
		return cnt + flash(data, 0);
	return 0;
}

void print(char *data)
{
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++)
			if (data[y * LINE + x] == BEYOND)
				printf(" ");
			else if (data[y * LINE + x] == JUSTFLASHED)
				printf("█");
			else
				printf("%c", data[y * LINE + x]);
		printf("\n");
	}
}

static int part_one(FILE *fp)
{
	int res = 0;

	WHOLE;

	int inc = 0;
	for (int i = 0; i < 101; i++) {
		for (int y = 0; y < SIZE; y++)
			for (int x = 0; x < SIZE; x++)
				INC(x, y);
		res += flash(data, 0);
		for (int y = 0; y < SIZE; y++)
			for (int x = 0; x < SIZE; x++)
				if (data[y * LINE + x] == JUSTFLASHED)
					data[y * LINE + x] = '0';
	}

	free(data);

	return res + 2;
}

static int part_two(FILE *fp)
{
	int res = 0;

	WHOLE;

	int inc = 0, cnt = 0;
	for (res = 0; cnt != SIZE * SIZE - 1; res++) {
		for (int y = 0; y < SIZE; y++)
			for (int x = 0; x < SIZE; x++)
				INC(x, y);
		cnt = flash(data, 0);
		for (int y = 0; y < SIZE; y++)
			for (int x = 0; x < SIZE; x++)
				if (data[y * LINE + x] == JUSTFLASHED)
					data[y * LINE + x] = '0';
	}

	free(data);

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
