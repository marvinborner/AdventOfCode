#include <limits.h>
#include <openssl/md5.h>
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

#define FORCH                                                                                      \
	char ch = 0;                                                                               \
	while ((ch = fgetc(fp)) != EOF)

#define WHOLE                                                                                      \
	fseek(fp, 0, SEEK_END);                                                                    \
	long fsize = ftell(fp);                                                                    \
	fseek(fp, 0, SEEK_SET);                                                                    \
	char *data = malloc(fsize + 1);                                                            \
	fread(data, 1, fsize, fp);                                                                 \
	data[fsize] = 0;                                                                           \
	data[fsize--] = 0

#define FREEWHOLE free(data)

static int part_one(FILE *fp)
{
	int res = 0;

	WHOLE;

	char *string = malloc(fsize + 64);
	strcpy(string, data);

	while (1) {
		res++;

		int cnt = sprintf(string + fsize, "%d", res);

		char out[64] = { 0 };
		unsigned char *hash =
			MD5((unsigned char *)string, fsize + cnt, (unsigned char *)out);
		/* for (int i = 0; i < 16; i++) */
		/* 	printf("%02x", hash[i]); */
		/* putchar('\n'); */

		int sum = 0;
		for (int i = 0; i < 2; i++)
			sum += hash[i];
		sum += hash[2] & 0xf0;
		if (sum == 0)
			break;
	}

	free(string);
	FREEWHOLE;

	return res;
}

static int part_two(FILE *fp)
{
	int res = 0;

	WHOLE;

	char *string = malloc(fsize + 64);
	strcpy(string, data);

	while (1) {
		res++;

		int cnt = sprintf(string + fsize, "%d", res);

		char out[64] = { 0 };
		unsigned char *hash =
			MD5((unsigned char *)string, fsize + cnt, (unsigned char *)out);
		/* for (int i = 0; i < 16; i++) */
		/* 	printf("%02x", hash[i]); */
		/* putchar('\n'); */

		int sum = 0;
		for (int i = 0; i < 3; i++)
			sum += hash[i];
		if (sum == 0)
			break;
	}

	free(string);
	FREEWHOLE;

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
