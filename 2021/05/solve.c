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

#define SIZE 1024
static void solve(FILE *fp)
{
	int one = 0, two = 0; // Parts

	int *straight = calloc(4, SIZE * SIZE);
	int *diagonal = calloc(4, SIZE * SIZE);

	FORLINE
	{
		int x1, y1, x2, y2;
		sscanf(line, "%d,%d -> %d,%d\n", &x1, &y1, &x2, &y2);

		int xstart = x1 <= x2 ? x1 : x2;
		int xend = x1 >= x2 ? x1 : x2;

		if (x1 == x2 || y1 == y2) { // Straight
			int ystart = y1 <= y2 ? y1 : y2;
			int yend = y1 >= y2 ? y1 : y2;

			for (int y = ystart; y <= yend; y++) {
				for (int x = xstart; x <= xend; x++) {
					straight[y * SIZE + x]++;
					diagonal[y * SIZE + x]++;
				}
			}
		} else { // Diagonal
			int xneg = x1 > x2 ? -1 : 1;
			int yneg = y1 > y2 ? -1 : 1;
			for (int a = 0; xstart + a <= xend; a++)
				diagonal[(y1 + a * yneg) * SIZE + (x1 + a * xneg)]++;
		}
	}
	FREELINE;

	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			if (straight[y * SIZE + x] >= 2)
				one++;
			if (diagonal[y * SIZE + x] >= 2)
				two++;
		}
	}

	free(straight);
	free(diagonal);

	printf("%d\n", one);
	printf("%d\n", two);
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	clock_t tic = clock();
	solve(fp);
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
