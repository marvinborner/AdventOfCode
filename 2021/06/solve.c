#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void iterate(long *timers, long *birth, long *cnt)
{
	long next = birth[0];
	birth[0] = birth[1];
	birth[1] = timers[0];

	long x = timers[0];
	for (int i = 0; i < 6; i++)
		timers[i] = timers[i + 1];
	timers[6] = x + next;
	*cnt += birth[1];
}

static void solve(FILE *fp)
{
	long timers[7] = { 0 };
	long birth[2] = { 0 };

	long cnt = 0;
	char ch;
	int timer;
	while (fscanf(fp, "%d%c", &timer, &ch) != EOF && (ch == ',' || ch == '\n')) {
		cnt++;
		timers[timer]++;
	}

	for (int i = 0; i < 80; i++)
		iterate(timers, birth, &cnt);
	printf("%lu\n", cnt);
	for (int i = 80; i < 256; i++)
		iterate(timers, birth, &cnt);
	printf("%lu\n", cnt);
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
