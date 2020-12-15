#include "../../lib/uthash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct num {
	int num;
	int index;
	UT_hash_handle hh;
};

int add(struct num **nums, int index, int num)
{
	struct num *n;
	HASH_FIND_INT(*nums, &num, n);
	if (!n) {
		n = malloc(sizeof(*n));
		n->index = index;
		n->num = num;
		HASH_ADD_INT(*nums, num, n);
		return 0;
	}
	int diff = index - n->index;
	n->index = index;
	return diff;
}

void calc(FILE *fp)
{
	struct num *nums = NULL;

	int num, index = 1;
	while (fscanf(fp, "%d,", &num) == 1)
		num = add(&nums, index++, num);

	while (index < 2020)
		num = add(&nums, index++, num);
	printf("%d\n", num);

	while (index < 30000000)
		num = add(&nums, index++, num);
	printf("%d\n", num);
}

int main(int argc, char *argv[])
{
	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	clock_t tic = clock();
	calc(fp);
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
