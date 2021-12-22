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

#define AAH 100
static int part_one(FILE *fp)
{
	int res = 0;

	char cubes[AAH][AAH][AAH] = { 0 };

	char state[4];
	int xmin, xmax, ymin, ymax, zmin, zmax;
	while (fscanf(fp, "%[^ ] x=%d..%d,y=%d..%d,z=%d..%d\n", state, &xmin, &xmax, &ymin, &ymax,
		      &zmin, &zmax) == 7)
		for (int x = MAX(xmin, -(AAH / 2)); x <= MIN(xmax, (AAH / 2)); x++)
			for (int y = MAX(ymin, -(AAH / 2)); y <= MIN(ymax, (AAH / 2)); y++)
				for (int z = MAX(zmin, -(AAH / 2)); z <= MIN(zmax, (AAH / 2)); z++)
					cubes[x + (AAH / 2)][y + (AAH / 2)][z + (AAH / 2)] =
						state[1] == 'n';

	for (int x = 0; x < COUNT(cubes); x++)
		for (int y = 0; y < COUNT(cubes[x]); y++)
			for (int z = 0; z < COUNT(cubes[x][y]); z++)
				if (cubes[x][y][z])
					res++;

	return res;
}

static int int_compare(const void *a, const void *b)
{
	return (*(const int *)a - *(const int *)b);
}

#define SIZE 1024
static long part_two(FILE *fp)
{
	long res = 0;

	struct all {
		enum { HILFE, ON, OFF } state;
		long xmin, xmax;
		long ymin, ymax;
		long zmin, zmax;
	};
	struct all all[SIZE] = { 0 };

	long x[SIZE] = { 0 };
	long y[SIZE] = { 0 };
	long z[SIZE] = { 0 };
	int cnt = 0;

	char state[4];
	long _xmin, _xmax, _ymin, _ymax, _zmin, _zmax;
	while (fscanf(fp, "%[^ ] x=%ld..%ld,y=%ld..%ld,z=%ld..%ld\n", state, &_xmin, &_xmax, &_ymin,
		      &_ymax, &_zmin, &_zmax) == 7) {
		all[cnt].state = state[1] == 'n' ? ON : OFF;
		all[cnt].xmin = _xmin;
		all[cnt].xmax = _xmax;
		all[cnt].ymin = _ymin;
		all[cnt].ymax = _ymax;
		all[cnt].zmin = _zmin;
		all[cnt].zmax = _zmax;

		x[cnt] = _xmin;
		x[cnt + 1] = _xmax + 1;
		y[cnt] = _ymin;
		y[cnt + 1] = _ymax + 1;
		z[cnt] = _zmin;
		z[cnt + 1] = _zmax + 1;

		cnt += 2;
	}

	for (int i = 0; i < cnt / 2; i++) {
		struct all temp = all[i];
		all[i] = all[cnt - 1 - i];
		all[cnt - 1 - i] = temp;
	}

	qsort(x, cnt, sizeof(*x), int_compare);
	qsort(y, cnt, sizeof(*y), int_compare);
	qsort(z, cnt, sizeof(*z), int_compare);

	for (int i = 0; i < cnt - 1; i++) {
		long xmin = x[i];
		long xmax = x[i + 1];

		// TODO: all_* array size should be <SIZE for performance
		struct all all_x[SIZE] = { 0 };
		int all_x_cnt = -1;
		for (int a = 0; a < cnt; a++)
			if (xmin >= all[a].xmin && xmin <= all[a].xmax)
				all_x[++all_x_cnt] = all[a];

		for (int j = 0; j < cnt - 1; j++) {
			long ymin = y[j];
			long ymax = y[j + 1];

			struct all all_y[SIZE] = { 0 };
			int all_y_cnt = -1;
			for (int a = 0; a < cnt; a++)
				if (ymin >= all_x[a].ymin && ymin <= all_x[a].ymax)
					all_y[++all_y_cnt] = all_x[a];

			for (int k = 0; k < cnt - 1; k++) {
				long zmin = z[k];
				long zmax = z[k + 1];

				for (int a = 0; a < cnt; a++) {
					if (zmin >= all_y[a].zmin && zmin <= all_y[a].zmax) {
						if (all_y[a].state == ON)
							res += (xmax - xmin) * (ymax - ymin) *
							       (zmax - zmin);
						break;
					}
				}
			}
		}
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
	printf("%lu\n", part_two(fp));
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
