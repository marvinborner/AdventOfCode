#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const int xs[] = { 14, 14, 14, 12, 15, -12, -12, 12, -7, 13, -8, -5, -10, -7 };
static const int ys[] = { 14, 2, 1, 13, 5, 5, 5, 9, 3, 13, 2, 1, 11, 8 };
static const int zs[] = { 1, 1, 1, 1, 1, 26, 26, 1, 26, 1, 26, 26, 26, 26 };

int main(int argc, char *argv[])
{
	srand(time(0));
	long w = 19599999999999;

	char ws[15];
	while (1) {
		sprintf(ws, "%lu", w);

		long x = 0, y = 0, z = 0;
		for (int i = 0; i < 14; i++) {
			x = z;
			x %= 26;
			z /= zs[i];
			x += xs[i];
			x = (x == (ws[i] - '0')) ? 0 : 1;
			y = 25;
			y *= x;
			y += 1;
			z *= y;
			y = (ws[i] - '0') + ys[i];
			y *= x;
			z += y;
		}
		if (z == 0) {
			printf("Found %ld %ld %ld -> %ld\n", w, x, y, z);
			break;
		}
		if (w % 100000 == 0)
			printf("%ld %ld\n", w, z);
		w--;
	}
	return 0;
}
