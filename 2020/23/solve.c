#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SZ 9

int *play(int *I, int C, int M)
{
	int *c = malloc((C + 1) * sizeof(*c));
	if (!c)
		exit(1);

	for (int i = 0; i < C; i++)
		c[i] = i + 1;

	for (int i = 0; i < C + 1; i++)
		c[I[i]] = I[(i + 1) % SZ];

	c[0] = I[0];
	if (C > SZ) {
		c[I[SZ - 1]] = SZ + 1;
		c[C] = I[0];
	}

	for (int m = 1; m <= M; m++) {
		int p1 = c[c[0]];
		int p2 = c[c[c[0]]];
		int p3 = c[c[c[c[0]]]];
		int d = c[0] - 1 ? c[0] - 1 : C;
		while (p1 == d || p2 == d || p3 == d)
			d = d - 1 ? d - 1 : C;
		c[c[0]] = c[p3];
		c[p3] = c[d];
		c[d] = p1;
		c[0] = c[c[0]];
	}

	return c;
}

int main(int argc, char *argv[])
{
	int data[] = { 4, 6, 3, 5, 2, 8, 1, 7, 9 };
	int *d = malloc((1e6 + 1) * sizeof(*d));
	memcpy(d, data, 9 * 4);
	int *c = play(d, 1e6, 1e7);
	long res = ((long)c[1]) * ((long)c[c[1]]);
	printf("%lu\n", res);
	free(d);
	free(c);
	return 0;
}
