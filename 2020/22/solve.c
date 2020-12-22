#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

long part_one(FILE *fp)
{
	long res = 0;

	int player_one[512] = { 0 }, player_two[512] = { 0 };
	int one_low = 0, one_high = 0, two_low = 0, two_high = 0;

	char *line = NULL;
	size_t len;
	int paragraph = 0;
	int index = 0;
	while (getline(&line, &len, fp) != -1) {
		if (line[0] == '\n') {
			index = 0;
			paragraph++;
			continue;
		} else if (line[0] == 'P') {
			continue;
		} else {
			int num;
			sscanf(line, "%d", &num);
			if (paragraph == 0)
				player_one[index++] = num;
			else
				player_two[index++] = num;
		}
	}

	one_high = two_high = index;

	int cnt = 0;
	while (1) {
		int c1 = player_one[one_low++];
		int c2 = player_two[two_low++];
		cnt++;

		if (!c1 || !c2)
			break;

		if (c1 > c2) {
			player_one[one_high++] = c1;
			player_one[one_high++] = c2;
		} else {
			player_two[two_high++] = c2;
			player_two[two_high++] = c1;
		}
	}

	int *winner = one_low == one_high + 1 ? player_two : player_one;
	int low = one_low == one_high + 1 ? two_low : one_low;
	int high = one_low == one_high + 1 ? two_high : one_high;

	for (int i = high - low + 1, j = 0; i > 0; i--, j++)
		res += i * winner[two_low + j - 1];

	return res;
}

long part_two(FILE *fp)
{
	long res = 0;

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
