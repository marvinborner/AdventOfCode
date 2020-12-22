#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER 10000
#define DUP_SIZE 10000

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
	free(line);

	one_high = two_high = index;

	while (1) {
		int c1 = player_one[one_low++];
		int c2 = player_two[two_low++];

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

	int two_won = one_low == one_high + 1;
	int *winner = two_won ? player_two : player_one;
	int low = two_won ? two_low : one_low;
	int high = two_won ? two_high : one_high;

	for (int i = high - low + 1, j = 0; i > 0; i--, j++)
		res += i * winner[low + j - 1];

	return res;
}

// Returns 0 if one won, 1 if two won
int recursive(int *player_one, int *player_two, int *one_low, int *one_high, int *two_low,
	      int *two_high, int iter)
{
	int one_copy[BUFFER] = { 0 }, two_copy[BUFFER] = { 0 };
	memcpy(&one_copy[*one_low], &player_one[*one_low], (*one_high - *one_low) * sizeof(int));
	memcpy(&two_copy[*two_low], &player_two[*two_low], (*two_high - *two_low) * sizeof(int));

	int dup_ind = 0;
	int(*dup_one)[DUP_SIZE] = malloc(DUP_SIZE * BUFFER * sizeof(int));
	int(*dup_two)[DUP_SIZE] = malloc(DUP_SIZE * BUFFER * sizeof(int));

	while (1) {
		// Check for duplicates.. (hashmaps would be nice)
		for (int i = 0; i < dup_ind; i++) {
			if (!memcmp(dup_one[i], &one_copy[*one_low],
				    (*one_high - *one_low + 1) * sizeof(int)) ||
			    !memcmp(dup_two[i], &two_copy[*two_low],
				    (*two_high - *two_low + 1) * sizeof(int))) {
				free(dup_one);
				free(dup_two);
				return 0;
			}
		}
		memcpy(dup_one[dup_ind], &one_copy[*one_low], (*one_high - *one_low) * sizeof(int));
		memcpy(dup_two[dup_ind++], &two_copy[*two_low],
		       (*two_high - *two_low) * sizeof(int));
		if (dup_ind >= DUP_SIZE)
			exit(1);

		/* for (int *p = &one_copy[*one_low]; *p; p++) */
		/* 	printf("%d ", *p); */
		/* printf(" (L1: %d, H1: %d)\n", *one_low, *one_high); */
		/* for (int *p = &two_copy[*two_low]; *p; p++) */
		/* 	printf("%d ", *p); */
		/* printf(" (L2: %d, H2: %d)\n\n", *two_low, *two_high); */

		int c1 = one_copy[(*one_low)++];
		int c2 = two_copy[(*two_low)++];

		if (!c1 || !c2)
			break;

		int rec_won = -1;
		if (*one_high + 1 - *one_low > c1 && *two_high + 1 - *two_low > c2) {
			/* printf("AAH RECURSION: %d %d\n", c1, c2); */
			int rec_one_low = *one_low;
			int rec_one_high = *one_low + c1;
			int rec_two_low = *two_low;
			int rec_two_high = *two_low + c2;
			rec_won = recursive(one_copy, two_copy, &rec_one_low, &rec_one_high,
					    &rec_two_low, &rec_two_high, iter + 1);
			/* printf("REC: %d\n", rec_won); */
		}

		if (rec_won == -1) {
			if (c1 > c2) {
				one_copy[(*one_high)++] = c1;
				one_copy[(*one_high)++] = c2;
			} else {
				two_copy[(*two_high)++] = c2;
				two_copy[(*two_high)++] = c1;
			}
		} else {
			if (rec_won) {
				two_copy[(*two_high)++] = c2;
				two_copy[(*two_high)++] = c1;
			} else {
				one_copy[(*one_high)++] = c1;
				one_copy[(*one_high)++] = c2;
			}
		}
	}

	if (iter == 0) {
		memcpy(player_one, one_copy, BUFFER);
		memcpy(player_two, two_copy, BUFFER);
	}

	free(dup_one);
	free(dup_two);

	return one_low != one_high + 1;
}

long part_two(FILE *fp)
{
	long res = 0;

	int player_one[BUFFER] = { 0 }, player_two[BUFFER] = { 0 };
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
	free(line);

	one_high = two_high = index;

	recursive(player_one, player_two, &one_low, &one_high, &two_low, &two_high, 0);

	int two_won = one_low == one_high + 1;
	int *winner = two_won ? player_two : player_one;
	int low = two_won ? two_low : one_low;
	int high = two_won ? two_high : one_high;

	for (int i = high - low + 1, j = 0; i > 0; i--, j++)
		res += i * winner[low + j - 1];

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
