#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10000
#define X_MAX 99
#define Y_MAX 97

// Quite magical, isn't it?
#define TOP_LEFT(x, y, p) (x != 0 && y != 0 ? *(p - X_MAX - 1) : 0)
#define TOP_CENTER(x, y, p) (y != 0 ? *(p - X_MAX) : 0)
#define TOP_RIGHT(x, y, p) (x != X_MAX && y != 0 ? *(p - X_MAX + 1) : 0)
#define LEFT(x, y, p) (x != 0 ? *(p - 1) : 0)
#define RIGHT(x, y, p) (x != X_MAX ? *(p + 1) : 0)
#define BOTTOM_LEFT(x, y, p) (x != 0 && y != Y_MAX ? *(p + X_MAX - 1) : 0)
#define BOTTOM_CENTER(x, y, p) (y != Y_MAX ? *(p + X_MAX) : 0)
#define BOTTOM_RIGHT(x, y, p) (x != X_MAX && y != Y_MAX ? *(p + X_MAX + 1) : 0)

#define ADJACENT(x, y, p)                                                                          \
	((TOP_LEFT(x, y, p) == '#') + (TOP_CENTER(x, y, p) == '#') + (TOP_RIGHT(x, y, p) == '#') + \
	 (LEFT(x, y, p) == '#') + (RIGHT(x, y, p) == '#') + (BOTTOM_LEFT(x, y, p) == '#') +        \
	 (BOTTOM_CENTER(x, y, p) == '#') + (BOTTOM_RIGHT(x, y, p) == '#'))

int count_one(char *buf1, char *buf2)
{
	int x = 0, y = 0;
	for (char *p = buf1; *p; p++) {
		if (*p == '.') {
			x++;
			buf2[p - buf1] = '.';
			continue;
		}

		if (*p == '\n') {
			x = 0;
			y++;
			buf2[p - buf1] = '\n';
			continue;
		}

		int cnt = ADJACENT(x, y, p);

		if (*p == 'L' && !cnt) {
			buf2[p - buf1] = '#';
		} else if (*p == '#' && cnt >= 4) {
			buf2[p - buf1] = 'L';
		} else {
			buf2[p - buf1] = *p;
		}

		x++;
	}

	if (memcmp(buf1, buf2, SIZE)) {
		return count_one(buf2, buf1); // Swap buffers
	} else {
		int cnt = 0;
		for (char *p = buf1; *p; p++) {
			if (*p == '#')
				cnt++;
		}
		return cnt;
	}
}

#define TL (1 << 0)
#define TC (1 << 1)
#define TR (1 << 2)
#define R (1 << 3)
#define BR (1 << 4)
#define BC (1 << 5)
#define BL (1 << 6)
#define L (1 << 7)
#define SET(d)                                                                                     \
	{                                                                                          \
		if (type == '#' || type == 'L')                                                    \
			found |= d;                                                                \
		if (type == '#')                                                                   \
			cnt++;                                                                     \
	}
int count_two(char *buf1, char *buf2)
{
	int x = 0, y = 0;
	for (char *p = buf1; *p; p++) {
		if (*p == '.') {
			x++;
			buf2[p - buf1] = '.';
			continue;
		}

		if (*p == '\n') {
			x = 0;
			y++;
			buf2[p - buf1] = '\n';
			continue;
		}

		int i = 0, found = 0, cnt = 0;
		char type;
		while (found != 0xff) {
			// Handle overflows (could be combined with the checks below)
			if (x - i <= 0 || y - i <= 0)
				found |= TL;
			if (y - i <= 0)
				found |= TC;
			if (x + i >= X_MAX - 2 || y - i <= 0)
				found |= TR;
			if (x + i >= X_MAX - 2)
				found |= R;
			if (x + i >= X_MAX - 2 || y + i >= Y_MAX)
				found |= BR;
			if (y + i >= Y_MAX)
				found |= BC;
			if (x - i <= 0 || y + i >= Y_MAX)
				found |= BL;
			if (x - i <= 0)
				found |= L;

			// Find next seat
			if ((found & TL) == 0 &&
			    (type = TOP_LEFT(x - i, y - i, &buf1[(y - i) * X_MAX + (x - i)])))
				SET(TL);
			if ((found & TC) == 0 &&
			    (type = TOP_CENTER(x, y - i, &buf1[(y - i) * X_MAX + x])))
				SET(TC);
			if ((found & TR) == 0 &&
			    (type = TOP_RIGHT(x + i, y - i, &buf1[(y - i) * X_MAX + (x + i)])))
				SET(TR);
			if ((found & R) == 0 &&
			    (type = RIGHT(x + i, y, &buf1[y * X_MAX + (x + i)])))
				SET(R);
			if ((found & BR) == 0 &&
			    (type = BOTTOM_RIGHT(x + i, y + i, &buf1[(y + i) * X_MAX + (x + i)])))
				SET(BR);
			if ((found & BC) == 0 &&
			    (type = BOTTOM_CENTER(x, y + i, &buf1[(y + i) * X_MAX + x])))
				SET(BC);
			if ((found & BL) == 0 &&
			    (type = BOTTOM_LEFT(x - i, y + i, &buf1[(y + i) * X_MAX + (x - i)])))
				SET(BL);
			if ((found & L) == 0 && (type = LEFT(x - i, y, &buf1[y * X_MAX + (x - i)])))
				SET(L);

			i++;
		}

		if (*p == 'L' && !cnt) {
			buf2[p - buf1] = '#';
		} else if (*p == '#' && cnt >= 5) {
			buf2[p - buf1] = 'L';
		} else {
			buf2[p - buf1] = *p;
		}

		x++;
	}

	if (memcmp(buf1, buf2, SIZE)) {
		return count_two(buf2, buf1); // Swap buffers
	} else {
		int cnt = 0;
		for (char *p = buf1; *p; p++) {
			if (*p == '#')
				cnt++;
		}
		return cnt;
	}
}

int part_one(char *data)
{
	int res = 0;

	char buf1[SIZE] = { 0 };
	memcpy(buf1, data, SIZE);
	char buf2[SIZE] = { 0 };
	memcpy(buf2, data, SIZE);

	return count_one(buf1, buf2);
}

int part_two(char *data)
{
	int res = 0;

	char buf1[SIZE] = { 0 };
	memcpy(buf1, data, SIZE);
	char buf2[SIZE] = { 0 };
	memcpy(buf2, data, SIZE);

	return count_two(buf1, buf2);
}

int main(int argc, char *argv[])
{
	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);
	char buf[SIZE] = { 0 };
	fread(buf, SIZE, 1, fp);

	clock_t tic = clock();
	printf("%d\n", part_one(buf));
	printf("%d\n", part_two(buf));
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
