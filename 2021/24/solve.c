#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COUNT(a) ((int)(sizeof(a) / sizeof 0 [a]))

#define FORLINE                                                                                    \
	char *line = NULL;                                                                         \
	size_t len = 0;                                                                            \
	while (getline(&line, &len, fp) != EOF)
#define FREELINE                                                                                   \
	if (line)                                                                                  \
	free(line)

typedef char block[17][16];

struct data {
	int idx;
	int value;
};

typedef char out[15];

static void solve(FILE *fp)
{
	block blocks[14] = { 0 };
	int block_idx = -1;
	int line_idx = 0;
	FORLINE
	{
		if (line[0] == 'i') {
			block_idx++;
			line_idx = 0;
			continue;
		}

		strcpy(blocks[block_idx][line_idx++], line);
	};
	FREELINE;

	out min = { 0 }, max = { 0 };

	struct data arr[100] = { 0 };
	int idx = 0;

	for (int i = 0; i < COUNT(blocks); i++) {
		if (blocks[i][3][6] == '1') {
			int num;
			sscanf(blocks[i][14], "add y %d", &num);
			arr[idx++] = (struct data){ i, num };
			continue;
		}

		int num;
		sscanf(blocks[i][4], "add x %d", &num);
		struct data data = arr[--idx];
		int d = data.value + num, j = i;
		if (d < 0) {
			j = data.idx;
			data.idx = i;
			d *= -1;
		}
		max[j] = '9';
		max[data.idx] = 9 - d + '0';
		min[j] = 1 + d + '0';
		min[data.idx] = '1';
	}

	printf("%s\n%s\n", max, min);
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
