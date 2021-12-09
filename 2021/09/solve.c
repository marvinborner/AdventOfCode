#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COUNT(a) ((int)(sizeof(a) / sizeof 0 [a]))

#define WHOLE                                                                                      \
	fseek(fp, 0, SEEK_END);                                                                    \
	long fsize = ftell(fp);                                                                    \
	fseek(fp, 0, SEEK_SET);                                                                    \
	char *data = malloc(fsize + 1);                                                            \
	fread(data, 1, fsize, fp);                                                                 \
	data[fsize] = 0;

#define X 100
#define Y 100
#define MAGIC 0x80
#define _GET(x, y) data[(y) * (X + 1) + (x)]
#define GET(x, y) ((_GET(x, y) & ~MAGIC) & 0xff)
static void solve(FILE *fp)
{
	int res = 0;

	WHOLE;

	int basin(int x, int y)
	{
		if (x < 0 || x >= X || y < 0 || y >= Y || (_GET(x, y) & MAGIC) || GET(x, y) == '9')
			return 0;
		_GET(x, y) |= MAGIC;
		return basin(x + 1, y) + basin(x - 1, y) + basin(x, y + 1) + basin(x, y - 1) + 1;
	}

	int basins[3] = { 0 };
	for (int y = 0; y < Y; y++) {
		for (int x = 0; x < X; x++) {
			char a = GET(x, y);
			if (!((x < 1 || GET(x - 1, y) > a) && (x + 1 >= X || GET(x + 1, y) > a) &&
			      ((y < 1 || GET(x, y - 1) > a) && (y + 1 >= Y || GET(x, y + 1) > a))))
				continue;

			int b = basin(x, y);
			for (int i = 0; i < COUNT(basins); i++) {
				if (b > basins[i]) {
					for (int j = i; j < COUNT(basins); j++) {
						if (basins[i] > basins[j]) {
							basins[j] = basins[i];
							break;
						}
					}
					basins[i] = b;
					break;
				}
			}
			res += a - '0' + 1;
		}
	}
	free(data);

	printf("%d\n", res);
	printf("%d\n", basins[0] * basins[1] * basins[2]);
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
