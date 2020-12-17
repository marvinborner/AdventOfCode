#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 30
#define X_SIZE SIZE
#define Y_SIZE SIZE
#define Z_SIZE SIZE
#define W_SIZE SIZE
#define X_START (X_SIZE / 2)
#define Y_START (Y_SIZE / 2)
#define Z_START (Z_SIZE / 2)
#define W_START (W_SIZE / 2)

int part_one(FILE *fp)
{
	int res = 0;

	static char dat[X_SIZE][Y_SIZE][Z_SIZE] = { 0 };
	static char new[X_SIZE][Y_SIZE][Z_SIZE] = { 0 };

	char c;
	int x = X_START, y = Y_START, z = Z_START;
	for (; (c = fgetc(fp)) != EOF; x++) {
		if (c == '#') {
			dat[z][y][x] = 1;
			res++;
		} else if (c == '\n') {
			x = X_START - 1;
			y++;
		}
	}

	for (int i = 0; i < 6; i++) {
		memset(new, 0, X_SIZE * Y_SIZE * Z_SIZE);
		// LOL
		for (int z = 1; z < Z_SIZE - 1; z++)
		for (int y = 1; y < Y_SIZE - 1; y++)
		for (int x = 1; x < X_SIZE - 1; x++)
		for (int z2 = z - 1; z2 < z + 2; z2++)
		for (int y2 = y - 1; y2 < y + 2; y2++)
		for (int x2 = x - 1; x2 < x + 2; x2++)
			if ((z != z2 || y != y2 || x != x2) && dat[z2][y2][x2])
				new[z][y][x]++;

		for (int z = 1; z < Z_SIZE - 1; z++)
		for (int y = 1; y < Y_SIZE - 1; y++)
		for (int x = 1; x < X_SIZE - 1; x++)
			if ((new[z][y][x] == 2 && dat[z][y][x]) || new[z][y][x] == 3) {
				if (dat[z][y][x])
					continue;
				dat[z][y][x] = 1;
				res++;
			} else {
				if (!dat[z][y][x])
					continue;
				dat[z][y][x] = 0;
				res--;
			}
	}

	return res;
}

int part_two(FILE *fp)
{
	int res = 0;

	static char dat[W_SIZE][X_SIZE][Y_SIZE][Z_SIZE] = { 0 };
	static char new[W_SIZE][X_SIZE][Y_SIZE][Z_SIZE] = { 0 };

	char c;
	int x = X_START, y = Y_START, z = Z_START, w = W_START;
	for (; (c = fgetc(fp)) != EOF; x++) {
		if (c == '#') {
			dat[w][z][y][x] = 1;
			res++;
		} else if (c == '\n') {
			x = X_START - 1;
			y++;
		}
	}

	for (int i = 0; i < 6; i++) {
		memset(new, 0, X_SIZE * Y_SIZE * Z_SIZE);
		// LOL LOL
		for (int w = 1; w < W_SIZE - 1; w++)
		for (int z = 1; z < Z_SIZE - 1; z++)
		for (int y = 1; y < Y_SIZE - 1; y++)
		for (int x = 1; x < X_SIZE - 1; x++)
		for (int w2 = w - 1; w2 < w + 2; w2++)
		for (int z2 = z - 1; z2 < z + 2; z2++)
		for (int y2 = y - 1; y2 < y + 2; y2++)
		for (int x2 = x - 1; x2 < x + 2; x2++)
			if ((w != w2 || z != z2 || y != y2 || x != x2) && dat[w2][z2][y2][x2])
				new[w][z][y][x]++;

		for (int w = 1; w < W_SIZE - 1; w++)
		for (int z = 1; z < Z_SIZE - 1; z++)
		for (int y = 1; y < Y_SIZE - 1; y++)
		for (int x = 1; x < X_SIZE - 1; x++)
			if ((new[w][z][y][x] == 2 && dat[w][z][y][x]) || new[w][z][y][x] == 3) {
				if (dat[w][z][y][x])
					continue;
				dat[w][z][y][x] = 1;
				res++;
			} else {
				if (!dat[w][z][y][x])
					continue;
				dat[w][z][y][x] = 0;
				res--;
			}
	}

	return res;
}

int main(int argc, char *argv[])
{
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
