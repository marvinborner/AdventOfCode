#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ABS(a) ((a) < 0 ? -(a) : (a))

static void solve(FILE *fp)
{
	int crabs[1024] = { 0 };
	long cnt = 0;
	char ch;
	int pos, max = 0;
	while (fscanf(fp, "%d%c", &pos, &ch) != EOF && (ch == ',' || ch == '\n')) {
		crabs[cnt++] = pos;
		if (pos > max)
			max = pos;
	}

	int fuel1 = 0xfffffff, fuel2 = fuel1;
	for (int i = 0; i < max; i++) {
		int a = 0, b = 0;
		for (int j = 0; j < cnt; j++) {
			a += ABS(crabs[j] - i);
			int d = ABS(crabs[j] - i);
			b += (d * (d + 1)) / 2;
		}

		if (a < fuel1)
			fuel1 = a;

		if (b < fuel2)
			fuel2 = b;
	}

	printf("%d\n%d\n", fuel1, fuel2);
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
