#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ABS(a) ((a) < 0 ? -(a) : (a))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define COUNT(a) ((int)(sizeof(a) / sizeof 0 [a]))

#define FORLINE                                                                                    \
	char *line = NULL;                                                                         \
	size_t len = 0;                                                                            \
	while (getline(&line, &len, fp) != EOF)
#define FREELINE                                                                                   \
	if (line)                                                                                  \
	free(line)

#define FORCH                                                                                      \
	char ch = 0;                                                                               \
	while ((ch = fgetc(fp)) != EOF)

#define WHOLE                                                                                      \
	fseek(fp, 0, SEEK_END);                                                                    \
	long fsize = ftell(fp);                                                                    \
	fseek(fp, 0, SEEK_SET);                                                                    \
	char *data = malloc(fsize + 1);                                                            \
	fread(data, 1, fsize, fp);                                                                 \
	data[fsize] = 0;

static int part_one(FILE *fp)
{
	int pos1, pos2;
	fscanf(fp, "Player 1 starting position: %d\nPlayer 2 starting position: %d", &pos1, &pos2);

	int score1 = 0, score2 = 0;
	int player = 0;
	int a = 1, b = 2, c = 3;
	int aah = 0;
	while (score1 < 1000 && score2 < 1000) {
		aah += 3;
		if (player == 0) {
			pos1 += (a += 3) + (b += 3) + (c += 3);
			if (pos1 > 10)
				pos1 = pos1 % 10 + 1;
			score1 += pos1;
			player = 1;
		} else if (player == 1) {
			pos2 += (a += 3) + (b += 3) + (c += 3);
			if (pos2 > 10)
				pos2 = pos2 % 10 + 1;
			score2 += pos2;
			player = 0;
		}
	}

	return MIN(score1, score2) * aah;
}

struct won {
	long a, b;
};

static struct {
	int exists;
	struct won won;
} cache[10][10][21][21] = { 0 };

static struct won count(long player1, long player2, long score1, long score2)
{
	if (cache[player1 - 1][player2 - 1][score1][score2].exists)
		return cache[player1 - 1][player2 - 1][score1][score2].won;

	struct won won = { 0 };
	for (int a = 1; a <= 3; a++) {
		for (int b = 1; b <= 3; b++) {
			for (int c = 1; c <= 3; c++) {
				int sum = a + b + c;
				long player_switch = (player1 + sum - 1) % 10 + 1;
				long score_switch = score1 + player_switch;
				if (score_switch >= 21) {
					won.a += 1;
				} else {
					// Switch
					struct won aah =
						count(player2, player_switch, score2, score_switch);
					won.a += aah.b;
					won.b += aah.a;
				}
			}
		}
	}

	cache[player1 - 1][player2 - 1][score1][score2].exists = 1;
	cache[player1 - 1][player2 - 1][score1][score2].won = won;

	return won;
}

static long part_two(FILE *fp)
{
	int player1, player2;
	fscanf(fp, "Player 1 starting position: %d\nPlayer 2 starting position: %d", &player1,
	       &player2);

	struct won won = count(player1, player2, 0, 0);
	return MAX(won.a, won.b);
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	clock_t tic = clock();
	printf("%d\n", part_one(fp));
	rewind(fp);
	printf("%lu\n", part_two(fp));
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
