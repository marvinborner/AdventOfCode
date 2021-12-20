#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WHOLE                                                                                      \
	fseek(fp, 0, SEEK_END);                                                                    \
	long fsize = ftell(fp);                                                                    \
	fseek(fp, 0, SEEK_SET);                                                                    \
	char *data = malloc(fsize + 1);                                                            \
	fread(data, 1, fsize, fp);                                                                 \
	data[fsize] = 0;

#define SIZE 100
#define MULTI (SIZE + 10) // idk
#define LINE (SIZE + 1)
#define GET(x, y) image[(y) * (SIZE + MULTI) + (x)]
static void solve(FILE *fp)
{
	WHOLE;

	char buff[(SIZE + MULTI) * (SIZE + MULTI)];
	char image[(SIZE + MULTI) * (SIZE + MULTI)];
	for (int y = 0; y < SIZE; y++)
		for (int x = 0; x < SIZE; x++)
			buff[(y + MULTI / 2) * (SIZE + MULTI) + (x + MULTI / 2)] =
				data[514 + (y * LINE + x)];

	int offset = 1;

aah:;
	memset(image, offset % 2 == 0 ? '#' : '.', sizeof(image)); // Due to alg[0]
	for (int y = MULTI / 2 - offset + 1; y < SIZE + MULTI / 2 + offset - 1; y++)
		for (int x = MULTI / 2 - offset + 1; x < SIZE + MULTI / 2 + offset - 1; x++)
			image[y * (SIZE + MULTI) + x] = buff[y * (SIZE + MULTI) + x];

	for (int y = MULTI / 2 - offset; y < SIZE + MULTI / 2 + offset; y++) {
		for (int x = MULTI / 2 - offset; x < SIZE + MULTI / 2 + offset; x++) {
			int algorithm = ((GET(x - 1, y - 1) == '#') << 8) |
					((GET(x - 0, y - 1) == '#') << 7) |
					((GET(x + 1, y - 1) == '#') << 6) |
					((GET(x - 1, y - 0) == '#') << 5) |
					((GET(x - 0, y - 0) == '#') << 4) |
					((GET(x + 1, y - 0) == '#') << 3) |
					((GET(x - 1, y + 1) == '#') << 2) |
					((GET(x - 0, y + 1) == '#') << 1) |
					((GET(x + 1, y + 1) == '#') << 0);

			buff[y * (SIZE + MULTI) + x] = data[algorithm];
		}
	}

	if (offset == 2 || offset == 50) {
		int res = 0;
		for (unsigned int i = 0; i < sizeof(buff); i++)
			if (buff[i] == '#')
				res++;
		printf("%d\n", res);
	}
	if (offset == 50) {
		free(data);
		return;
	}
	offset++;
	goto aah;
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
