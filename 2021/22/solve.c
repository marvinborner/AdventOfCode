#include <limits.h>
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
	fread(data, 1, fsize, fp);                                                                 \
	data[fsize] = 0;
/* data[fsize--] = 0 */

static int part_one(FILE *fp)
{
	int res = 0;

	char cubes[100][100][100] = { 0 };

	char state[4];
	int xmin, xmax, ymin, ymax, zmin, zmax;
	while (fscanf(fp, "%[^ ] x=%d..%d,y=%d..%d,z=%d..%d\n", state, &xmin, &xmax, &ymin, &ymax,
		      &zmin, &zmax) == 7) {
		xmin = MAX(xmin, -50);
		xmax = MIN(xmax, 50);
		ymin = MAX(ymin, -50);
		ymax = MIN(ymax, 50);
		zmin = MAX(zmin, -50);
		zmax = MIN(zmax, 50);

		for (int x = MAX(xmin, -50); x <= MIN(xmax, 50); x++) {
			for (int y = MAX(ymin, -50); y <= MIN(ymax, 50); y++) {
				for (int z = MAX(zmin, -50); z <= MIN(zmax, 50); z++) {
					if (state[1] == 'n') { // on
						cubes[x + 50][y + 50][z + 50] = 1;
					} else if (state[1] == 'f') { // off
						cubes[x + 50][y + 50][z + 50] = 0;
					} else {
						fprintf(stderr, "Fatal error\n");
					}
				}
			}
		}
	}

	for (int x = 0; x < 100; x++)
		for (int y = 0; y < 100; y++)
			for (int z = 0; z < 100; z++)
				if (cubes[x][y][z])
					res++;

	return res;
}

static long part_two(FILE *fp)
{
	long res = 0;

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
	printf("%lu\n", part_two(fp));
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
