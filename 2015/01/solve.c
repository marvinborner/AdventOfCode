#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int part_one(FILE *fp)
{
	int res = 0;

	char ch = 0;
	while ((ch = fgetc(fp)) != EOF) {
		if (ch == '(')
			res++;
		else if (ch == ')')
			res--;
	}

	return res;
}

int part_two(FILE *fp)
{
	int res = 0, floor = 0;

	char ch = 0;
	while ((ch = fgetc(fp)) != EOF) {
		res++;

		if (ch == '(')
			floor++;
		else if (ch == ')')
			floor--;

		if (floor == -1)
			break;
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
