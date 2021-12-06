#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

static long iterate(char *fish, long cnt)
{
	/* for (int i = 0; i < cnt; i++) */
	/* 	printf("%d,", fish[i]); */
	/* printf("\n"); */

	long ret = cnt;
	for (long i = 0; i < cnt; i++) {
		if (fish[i] == 0) {
			fish[i] = 6;
			fish[ret++] = 8;
		} else {
			fish[i]--;
		}
	}

	return ret;
}

static long solve(FILE *fp)
{
	char *fish = malloc(20000000000 * sizeof(char));

	long cnt = 0;
	char ch;
	while (fscanf(fp, "%d%c", (int *)&fish[cnt++], &ch) != EOF && (ch == ',' || ch == '\n'))
		;
	cnt -= 1; // newline

	for (int i = 0; i < 256; i++)
		cnt = iterate(fish, cnt);

	free(fish);

	return cnt;
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	clock_t tic = clock();
	printf("%lu\n", solve(fp));
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
