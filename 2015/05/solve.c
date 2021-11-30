#include <stdio.h>
#include <stdlib.h>
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

#define FORP for (const char *p = line; *p && p; p++)

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

	FORLINE
	{
		int vowels = 0, dub = 0, illegal = 0;
		FORP
		{
			if (*p == 'a' || *p == 'e' || *p == 'i' || *p == 'o' || *p == 'u')
				vowels++;

			if (p - line > 1 && *p == *(p - 1))
				dub++;

			if (p - line > 1 &&
			    ((*(p - 1) == 'a' && *p == 'b') || (*(p - 1) == 'c' && *p == 'd') ||
			     (*(p - 1) == 'p' && *p == 'q') || (*(p - 1) == 'x' && *p == 'y'))) {
				illegal = 1;
				break;
			}
		}

		if (vowels >= 3 && dub >= 1 && !illegal)
			res++;
	}
	FREELINE;

	return res;
}

static int part_two(FILE *fp)
{
	int res = 0;

	FORLINE
	{
		char dub[26] = { 0 };
		int betw = 0;
		FORP
		{
			// TODO: Dub
			if (p - line > 2 && *p == *(p - 2))
				betw++;
		}

		int dub_cnt = 0;
		for (int i = 0; i < 26; i++)
			if (dub[i] >= 2)
				dub_cnt++;

		if (dub_cnt >= 1 && betw)
			res++;
	}
	FREELINE;

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
