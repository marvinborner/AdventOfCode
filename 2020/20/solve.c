#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COUNT 10

enum cnt_pos { T, R, B, L };

struct tile {
	int id;

	int match[144];

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

void reverse(int dest[], int src[])
{
	for (int i = 0; i < COUNT; i++) {
		dest[COUNT - 1 - i] = src[i];
	}
}

long part_one(FILE *fp)
{
	long res = 1;

	struct tile tiles[144] = { 0 };
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
	}

	for (int i = 0; i < tile_cnt; i++) {
		struct tile *tile = &tiles[i];
		// Find adjacent
		int *cur, *cur_rev, cnt;
		for (int j = 0; j < 4; j++) { // TRBL
			switch (j) {
			case T:
				cnt = tile->cnt[T];
				cur = tile->top;
				cur_rev = tile->top_rev;
				break;
			case R:
				cnt = tile->cnt[R];
				cur = tile->right;
				cur_rev = tile->right_rev;
				break;
			case B:
				cnt = tile->cnt[B];
				cur = tile->bottom;
				cur_rev = tile->bottom_rev;
				break;
			case L:
				cnt = tile->cnt[L];
				cur = tile->left;
				cur_rev = tile->left_rev;
				break;
			default:
				exit(1);
				break;
			}

			for (int k = 0; k < tile_cnt; k++) {
				printf("%d: %d %d\n", cnt, tile->id, j);
				struct tile *cmp = &tiles[k];
				if (cmp->id == tile->id)
					continue;

				int match_cnt = 0;
				if (cnt == cmp->cnt[T]) {
					if (!memcmp(cur, cmp->top, 40)) {
						match_cnt++;
					} else if (!memcmp(cur_rev, cmp->top, 40)) {
						match_cnt++;
					}
				}
				if (cnt == cmp->cnt[R]) {
					if (!memcmp(cur, cmp->right, 40)) {
						match_cnt++;
					} else if (!memcmp(cur_rev, cmp->right, 40)) {
						match_cnt++;
					}
				}
				if (cnt == cmp->cnt[B]) {
					if (!memcmp(cur, cmp->bottom, 40)) {
						match_cnt++;
					} else if (!memcmp(cur_rev, cmp->bottom, 40)) {
						match_cnt++;
					}
				}
				if (cnt == cmp->cnt[L]) {
					if (!memcmp(cur, cmp->left, 40)) {
						match_cnt++;
					} else if (!memcmp(cur_rev, cmp->left, 40)) {
						match_cnt++;
					}
				}

				tile->match[k] += match_cnt;
			}
		}
	}

	for (int i = 0; i < tile_cnt; i++) {
		struct tile *tile = &tiles[i];

		int cnt = 0;
		for (int j = 0; j < tile_cnt; j++) {
			//if (tile->match[j] > cnt)
			cnt += tile->match[j];
		}

		printf("%d - %d\n", cnt, tile->id);
		/* res *= tile->id; */
		//printf("%d\n", tile->best_cnt);
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
