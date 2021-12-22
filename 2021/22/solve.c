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

#define CUBES 1000000

struct cube {
	char exists;
	int x, y, z;
};

static void add_cube(struct cube *cubes, int x, int y, int z)
{
	for (int i = 0; i < CUBES; i++) {
		if (!cubes[i].exists) {
			cubes[i].exists = 1;
			cubes[i].x = x;
			cubes[i].y = y;
			cubes[i].z = z;
			return;
		}
	}

	fprintf(stderr, "No more cubes left!\n");
	exit(1);
}

static void remove_cube(struct cube *cubes, int x, int y, int z)
{
	for (int i = 0; i < CUBES; i++) {
		if (cubes[i].exists && (cubes[i].x == x || cubes[i].y == y || cubes[i].z == z)) {
			cubes[i].exists = 0;
			return;
		}
	}
}

static int part_one(FILE *fp)
{
	int res = 0;

	struct cube *cubes = calloc(CUBES, sizeof(*cubes));

	char state[4];
	int xmin, xmax, ymin, ymax, zmin, zmax;
	while (fscanf(fp, "%[^ ] x=%d..%d,y=%d..%d,z=%d..%d\n", state, &xmin, &xmax, &ymin, &ymax,
		      &zmin, &zmax) == 7) {
		/* printf("%s %d..%d %d..%d %d..%d\n", state, xmin, xmax, ymin, ymax, zmin, ymax); */

		xmin = MAX(xmin, -50);
		xmax = MIN(xmax, 50);
		ymin = MAX(ymin, -50);
		ymax = MIN(ymax, 50);
		zmin = MAX(zmin, -50);
		zmax = MIN(zmax, 50);

		for (int x = xmin; x < xmax; x++) {
			for (int y = ymin; y < ymax; y++) {
				for (int z = zmin; z < zmax; z++) {
					/* printf("%d %d %d\n", x, y, z); */
					if (state[1] == 'n') { // on
						add_cube(cubes, x, y, z);
					} else if (state[1] == 'f') { // off
						remove_cube(cubes, x, y, z);
					} else {
						fprintf(stderr, "Fatal error\n");
					}
				}
			}
		}
	}

	return res;
}

static int part_two(FILE *fp)
{
	int res = 0;

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
