#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COUNT 10
#define SIZE (10 * sizeof(int))
#define INP_COUNT 144

#define FLIP_X (0b11 << 0)
#define FLIP_Y (0b11 << 2)
#define ROT_ONE (0b11 << 4)
#define ROT_TWO (0b11 << 6)
#define ROT_THREE (0b11 << 8)

enum cnt_pos { T, R, B, L };

struct tile {
	int id;

	int match[INP_COUNT];
	int reversed; // Bitmap

	char image[COUNT][COUNT];

	int cnt[4]; // cnt_pos
	int top[COUNT];
	int right[COUNT];
	int bottom[COUNT];
	int left[COUNT];
	int top_rev[COUNT];
	int right_rev[COUNT];
	int bottom_rev[COUNT];
	int left_rev[COUNT];
};

void set_rotation(int *reversed, int pos_a, int pos_b, int is_rev)
{
	int rot = abs((pos_a + 1) - (pos_b + 1));

	if (rot == 0)
		return;

	if (rot == 1 && !is_rev)
		*reversed |= ROT_ONE;
	else if (rot == 2 && !is_rev)
		*reversed |= ROT_TWO;
	else if (rot == 3 && !is_rev)
		*reversed |= ROT_THREE;

	if (is_rev && rot % 2 == 0) {
		*reversed |= FLIP_X;
	} else if (is_rev && rot % 2 == 1) {
		*reversed |= FLIP_Y;
	}
}

void reverse(int dest[], int src[])
{
	for (int i = 0; i < COUNT; i++) {
		dest[COUNT - 1 - i] = src[i];
	}
}

long part_one(FILE *fp)
{
	long res = 1;

	struct tile tiles[INP_COUNT] = { 0 };
	int tile_cnt = 0;

	char *line = NULL;
	size_t len;
	int y = 0;
	while (getline(&line, &len, fp) != -1) {
		int num;
		if (line[0] == '\n') {
			tile_cnt++;
		} else if (sscanf(line, "Tile %d:", &num) == 1) {
			struct tile new = { 0 };
			new.id = num;
			tiles[tile_cnt] = new;
			y = 0;
		} else {
			struct tile *tile = &tiles[tile_cnt];
			memcpy(tile->image, line, COUNT);
			if (y == 0) {
				for (int i = 0; i < COUNT; i++) {
					tile->top[i] = line[i] == '#';
					tile->cnt[T] += tile->top[i];
				}
			} else if (y == COUNT - 1) {
				for (int i = 0; i < COUNT; i++) {
					tile->bottom[i] = line[i] == '#';
					tile->cnt[B] += tile->bottom[i];
				}
			}
			tile->left[y] = line[0] == '#';
			tile->cnt[L] += tile->left[y];
			tile->right[y] = line[COUNT - 1] == '#';
			tile->cnt[R] += tile->right[y];
			y++;
		}
	}
	tile_cnt++;
	free(line);

	for (int i = 0; i < tile_cnt; i++) {
		struct tile *tile = &tiles[i];
		reverse(tile->top_rev, tile->top);
		reverse(tile->right_rev, tile->right);
		reverse(tile->bottom_rev, tile->bottom);
		reverse(tile->left_rev, tile->left);
	}

	for (int i = 0; i < tile_cnt; i++) {
		struct tile *tile = &tiles[i];
		// Find adjacent
		int *cur, cnt;
		for (int j = 0; j < 4; j++) { // TRBL
			switch (j) {
			case T:
				cnt = tile->cnt[T];
				cur = tile->top;
				break;
			case R:
				cnt = tile->cnt[R];
				cur = tile->right;
				break;
			case B:
				cnt = tile->cnt[B];
				cur = tile->bottom;
				break;
			case L:
				cnt = tile->cnt[L];
				cur = tile->left;
				break;
			default:
				exit(1);
				break;
			}

			for (int k = 0; k < tile_cnt; k++) {
				struct tile *cmp = &tiles[k];
				if (cmp->id == tile->id)
					continue;

				int match_cnt = 0, reversed = 0;
				if (cnt == cmp->cnt[T]) {
					if (!memcmp(cur, cmp->top, SIZE)) {
						set_rotation(&reversed, T, j, 0);
						match_cnt++;
					} else if (!memcmp(cur, cmp->top_rev, SIZE)) {
						set_rotation(&reversed, T, j, 1);
						match_cnt++;
					}
				}
				if (cnt == cmp->cnt[R]) {
					if (!memcmp(cur, cmp->right, SIZE)) {
						set_rotation(&reversed, R, j, 0);
						match_cnt++;
					} else if (!memcmp(cur, cmp->right_rev, SIZE)) {
						set_rotation(&reversed, R, j, 1);
						//reversed |= REV_RIGHT;
						match_cnt++;
					}
				}
				if (cnt == cmp->cnt[B]) {
					if (!memcmp(cur, cmp->bottom, SIZE)) {
						set_rotation(&reversed, B, j, 0);
						match_cnt++;
					} else if (!memcmp(cur, cmp->bottom_rev, SIZE)) {
						set_rotation(&reversed, B, j, 1);
						//reversed |= REV_BOTTOM;
						match_cnt++;
					}
				}
				if (cnt == cmp->cnt[L]) {
					if (!memcmp(cur, cmp->left, SIZE)) {
						set_rotation(&reversed, L, j, 0);
						match_cnt++;
					} else if (!memcmp(cur, cmp->left_rev, SIZE)) {
						set_rotation(&reversed, L, j, 1);
						//reversed |= REV_LEFT;
						match_cnt++;
					}
				}

				tile->match[k] += match_cnt;
				if (reversed != 0)
					cmp->reversed = reversed;
			}
		}
	}

	for (int i = 0; i < tile_cnt; i++) {
		struct tile *tile = &tiles[i];

		if (tile->reversed)
			printf("%d: %x\n", tile->id, tile->reversed);
		int cnt = 0, flipped = 0;
		for (int j = 0; j < tile_cnt; j++) {
			cnt += tile->match[j];
		}

		if (cnt == 2) {
			res *= tile->id;
		}
	}

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
