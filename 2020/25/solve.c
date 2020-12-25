#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAGIC 20201227

long part_one(FILE *fp)
{
	long res = 1;

	int pub1, pub2;
	fscanf(fp, "%d\n%d", &pub1, &pub2);

	int loop1 = 1;
	long val = 1;
	while (val != pub1 && loop1++)
		val = (val * 7) % MAGIC;

	for (int i = 0; i < loop1 - 1; i++)
		res = (res * pub2) % MAGIC;
	return res;
}

long part_two(FILE *fp)
{
	long res = 0;
	// Merry christmas!
	return res;
}

int main(int argc, char *argv[])
{
	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	clock_t tic = clock();
	printf("%lu\n", part_one(fp));
	rewind(fp);
	printf("%lu\n", part_two(fp));
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
