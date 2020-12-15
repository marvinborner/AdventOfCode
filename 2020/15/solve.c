#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NUMS 30000000

static int nums[MAX_NUMS] = { 0 };

int part_one(FILE *fp, int count)
{
	long size = 0;
	while (size < count)
		if (fscanf(fp, "%d,", &nums[size++]) != 1)
			break;

	for (int i = size - 2; i < count - 1; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (nums[j] == nums[i]) {
				nums[i + 1] = i - j;
				break;
			}
		}
	}

	return nums[count - 1];
}

int main(int argc, char *argv[])
{
	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	clock_t tic = clock();
	printf("%d\n", part_one(fp, 2020));
	memset(nums, 0, 2020);
	rewind(fp);
	printf("%d\n", part_one(fp, 30000000));
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
