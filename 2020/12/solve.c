#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum dir { N, E, S, W };

// I <3 recursion
enum dir rotate(enum dir dir, int cnt, int r)
{
	if (!cnt)
		return dir;

	if (r) { // right
		if (dir == W)
			dir = N;
		else
			dir++;
	} else { // left
		if (dir == N)
			dir = W;
		else
			dir--;
	}
	return rotate(dir, cnt - 1, r);
}

// Quite inefficient but I like this approach.
int *rotate_wp(int dirs[], int cnt, int r)
{
	if (!cnt)
		return dirs;

	if (r) {
		int tmp = dirs[W];
		dirs[W] = dirs[S];
		dirs[S] = dirs[E];
		dirs[E] = dirs[N];
		dirs[N] = tmp;
	} else {
		int tmp = dirs[N];
		dirs[N] = dirs[E];
		dirs[E] = dirs[S];
		dirs[S] = dirs[W];
		dirs[W] = tmp;
	}

	return rotate_wp(dirs, cnt - 1, r);
}

int part_one(FILE *fp)
{
	char *line = NULL;
	size_t len = 0;
	int coords[4] = { 0 };
	enum dir cur = E;
	while (getline(&line, &len, fp) != -1) {
		char dir;
		int cnt;
		sscanf(line, "%c%d\n", &dir, &cnt);
		switch (dir) {
		case 'N':
			coords[N] += cnt;
			break;
		case 'E':
			coords[E] += cnt;
			break;
		case 'S':
			coords[S] += cnt;
			break;
		case 'W':
			coords[W] += cnt;
			break;
		case 'L':
			cur = rotate(cur, cnt / 90, 0);
			break;
		case 'R':
			cur = rotate(cur, cnt / 90, 1);
			break;
		case 'F':
			coords[cur] += cnt;
			break;
		default:
			break;
		}
	}

	return abs((coords[E] - coords[W]) + (coords[S] - coords[N]));
}

int part_two(FILE *fp)
{
	char *line = NULL;
	size_t len = 0;
	int wp[4] = { 1, 10, 0, 0 };
	int coords[4] = { 0 };
	enum dir cur = E;
	while (getline(&line, &len, fp) != -1) {
		char dir;
		int cnt;
		sscanf(line, "%c%d\n", &dir, &cnt);
		switch (dir) {
		case 'N':
			wp[N] += cnt;
			break;
		case 'E':
			wp[E] += cnt;
			break;
		case 'S':
			wp[S] += cnt;
			break;
		case 'W':
			wp[W] += cnt;
			break;
		case 'L':
			rotate_wp(wp, cnt / 90, 0);
			break;
		case 'R':
			rotate_wp(wp, cnt / 90, 1);
			break;
		case 'F':
			coords[N] += cnt * wp[N];
			coords[E] += cnt * wp[E];
			coords[S] += cnt * wp[S];
			coords[W] += cnt * wp[W];
			break;
		default:
			break;
		}
	}

	return abs((coords[E] - coords[W])) + abs((coords[S] - coords[N]));
}

int main(int argc, char *argv[])
{
	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	clock_t tic = clock();
	printf("%d\n", part_one(fp));
	rewind(fp);
	printf("%d\n", part_two(fp));
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
