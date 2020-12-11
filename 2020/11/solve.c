#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10000
#define X_MAX 99
#define Y_MAX 97

// Quite magical, isn't it?
#define ADJACENT(x, y, p)                                                                          \
	(x != 0 && y != 0 ? *(p - X_MAX - 1) == '#' : 0) + (y != 0 ? *(p - X_MAX) == '#' : 0) +    \
		(x != X_MAX && y != 0 ? *(p - X_MAX + 1) == '#' : 0) +                             \
		(x != 0 ? *(p - 1) == '#' : 0) + (x != X_MAX ? *(p + 1) == '#' : 0) +              \
		(x != 0 && y != Y_MAX ? *(p + X_MAX - 1) == '#' : 0) +                             \
		(y != Y_MAX ? *(p + X_MAX) == '#' : 0) +                                           \
		(x != X_MAX && y != Y_MAX ? *(p + X_MAX + 1) == '#' : 0);

int count(char *buf1, char *buf2)
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
		return count(buf2, buf1); // Swap buffers
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

	return count(buf1, buf2);
}

int part_two(char *data)
{
	int res = 0;

	return res;
}

int main(int argc, char *argv[])
{
	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);
	char buf[SIZE] = { 0 };
	fread(buf, SIZE, 1, fp);

	printf("%d\n", part_one(buf));
	printf("%d\n", part_two(buf));

	fclose(fp);
	return 0;
}
