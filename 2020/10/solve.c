#include <stdio.h>
#include <stdlib.h>

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

long part_two(int *data)
{
	long a, b, c;
	a = 1;
	b = 0;
	c = 0;
	for (int i = LENGTH - 2; i > 0; i--) {
		long next = (i + 1 < LENGTH && data[i + 1] - data[i] <= 3 ? a : 0) +
			    (i + 2 < LENGTH && data[i + 2] - data[i] <= 3 ? b : 0) +
			    (i + 3 < LENGTH && data[i + 3] - data[i] <= 3 ? c : 0);
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
	LENGTH = i + 2;

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
	data[LENGTH] = data[LENGTH - 1] + 3;

	printf("%d\n", part_one(data));
	printf("%lu\n", part_two(data));

	fclose(fp);
	return 0;
}
