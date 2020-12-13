#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int part_one(FILE *fp)
{
	int res = 0;

	char *line = NULL;
	size_t len = 0;
	while (getline(&line, &len, fp) != -1) {
		int low, high, cnt = 0;
		char ch;
		char str[42];
		sscanf(line, "%d-%d %c: %s\n", &low, &high, &ch, &str[0]);

		for (char *p = str; *p; p++)
			if (*p == ch)
				cnt++;

		if (cnt >= low && cnt <= high)
			res++;
	}

	return res;
}

int part_two(FILE *fp)
{
	int res = 0;

	char *line = NULL;
	size_t len = 0;
	while (getline(&line, &len, fp) != -1) {
		int low, high, cnt = 0;
		char ch, first, second;
		char str[256];
		sscanf(line, "%d-%d %c: %s\n", &low, &high, &ch, &str[0]);
		first = str[low - 1];
		second = str[high - 1];
		if (first == ch && second != ch || first != ch && second == ch)
			res++;
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
