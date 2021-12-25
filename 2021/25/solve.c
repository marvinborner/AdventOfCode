#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	fread(data, 1, fsize, fp);                                                                 \
	data[fsize] = 0;
/* data[fsize--] = 0 */

static int part_one(FILE *fp)
{
	int res = 0;

	char grid[200][200] = { 0 };
	char buf[200][200] = { 0 };

	int line_cnt = 0;
	FORLINE
	strcpy(grid[line_cnt++], line);
	FREELINE;

	memcpy(buf, grid, sizeof(buf));
	while (1) {
		res++;

		int moves = 0;

		// East
		for (int y = 0; y < line_cnt; y++) {
			for (int x = 0; x < COUNT(grid[y]); x++) {
				if (grid[y][x] != '>')
					continue;

				if (grid[y][x + 1] == '\n') { // End
					if (grid[y][0] == '.') {
						buf[y][x] = '.';
						buf[y][0] = '>';
						moves++;
					}
				} else if (grid[y][x + 1] == '.') {
					buf[y][x] = '.';
					buf[y][x + 1] = '>';
					moves++;
				}
			}
		}

		// South
		memcpy(grid, buf, sizeof(grid));
		for (int y = 0; y < line_cnt; y++) {
			for (int x = 0; x < COUNT(grid[y]); x++) {
				if (grid[y][x] != 'v')
					continue;

				if (grid[y + 1][x] == 0) { // End
					if (grid[0][x] == '.') {
						buf[y][x] = '.';
						buf[0][x] = 'v';
						moves++;
					}
				} else if (grid[y + 1][x] == '.') {
					buf[y][x] = '.';
					buf[y + 1][x] = 'v';
					moves++;
				}
			}
		}

		if (!moves)
			break;

		memcpy(grid, buf, sizeof(grid));
	}

	return res;
}

static int part_two(FILE *fp)
{
	int res = 42;

	(void)fp;

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
