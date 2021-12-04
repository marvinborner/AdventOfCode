#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int board[5][5];

// Very beautiful and efficient!!
static int check_board(board input, int *numbers, int cnt)
{
	board marked = { 0 };

	for (int i = 0; i < cnt; i++) {
		for (int y = 0; y < 5; y++) {
			for (int x = 0; x < 5; x++) {
				if (input[y][x] == numbers[i]) {
					marked[y][x] = 1;
					break;
				}
			}
		}
	}

	for (int y = 0; y < 5; y++) {
		int row = 0;
		for (int x = 0; x < 5; x++) {
			if (marked[y][x])
				row++;
		}
		if (row == 5)
			goto bingo;
	}

	for (int x = 0; x < 5; x++) {
		int column = 0;
		for (int y = 0; y < 5; y++) {
			if (marked[y][x])
				column++;
		}
		if (column == 5)
			goto bingo;
	}

	return 0;

bingo:;
	int res = 0;
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			if (!marked[y][x])
				res += input[y][x];
		}
	}
	return res;
}

static void solve(FILE *fp)
{
	int numbers[256] = { 0 };
	int cnt = 0;
	char ch = 0;
	while (fscanf(fp, "%d%c", &numbers[cnt], &ch) > 0 && ch == ',')
		cnt++;

	board boards[256];
	memset(boards, 0xffff, sizeof(board) * 256);

	int board_cnt = 0;
	int x = 0, y = 0;
	while (1) {
		if (fscanf(fp, "%d%c", &boards[board_cnt][x][y], &ch) < 1)
			break;

		if (x++ == 4) {
			y++;
			x = 0;
		}
		if (y == 5) {
			board_cnt++;
			x = 0;
			y = 0;
		}
	}

	int won = 0;
	for (int num = 0; num < cnt; num++) {
		for (int i = 0; i < board_cnt; i++) {
			if (boards[i][0][0] == 0x424242)
				continue;

			int bingo = 0;
			if ((bingo = check_board(boards[i], numbers, num + 1))) {
				boards[i][0][0] = 0x424242;
				won++;

				if (won == 1 || won == board_cnt)
					printf("%d\n", bingo * numbers[num]);
				if (won == board_cnt)
					return;
			}
		}
	}
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
