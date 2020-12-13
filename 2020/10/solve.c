#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int LENGTH = 0;

int part_one(int *data)
{
	int prev = 0, three = 1, one = 0;

	for (int i = 0; i < LENGTH; i++) {
		if (data[i] == 0)
			continue;
		if (data[i] - prev == 3)
			three++;
		else
			one++;
		prev = data[i];
	}

	return one * three;
}

#define COND(i, o) ((i) + (o) < LENGTH && *(cur + (o)) - *cur <= 3)
long part_two(int *data)
{
	long a = 1;
	long b = 0;
	long c = 0;

	int *cur = &data[LENGTH - 1];
	while (cur-- != &data[0]) {
		int i = cur - data;
		long next = (COND(i, 1) ? a : 0) + (COND(i, 2) ? b : 0) + (COND(i, 3) ? c : 0);
		c = b;
		b = a;
		a = next;
	}

	return a;
}

int cmp(const void *a, const void *b)
{
	int int_a = *((int *)a);
	int int_b = *((int *)b);

	if (int_a == int_b)
		return 0;
	else if (int_a < int_b)
		return -1;
	else
		return 1;
}

int *to_int(FILE *fp, int *arr)
{
	int d = 0, i = 0;
	while (fscanf(fp, "%d\n", &d) != EOF)
		arr[i++] = d;
	LENGTH = i + 1;

	return arr;
}

int main()
{
	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	int data[128] = { 0 };
	to_int(fp, data);
	qsort(data, LENGTH, sizeof(int), cmp);

	clock_t tic = clock();
	printf("%d\n", part_one(data));
	printf("%lu\n", part_two(data));
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
