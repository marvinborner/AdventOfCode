#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int x, y;
} vec2;

typedef struct {
	vec2 min;
	vec2 max;
} range;

#define IN_RANGE(pos, range)                                                                       \
	(pos.x >= range.min.x && pos.x <= range.max.x && pos.y >= range.min.y &&                   \
	 pos.y <= range.max.y)
#define ADD(a, b) (a = (vec2){ a.x + b.x, a.y + b.y })
#define DRAG(x) ((x) < 0 ? (x)++ : (x) > 0 ? (x)-- : (x))

static int hits(vec2 velocity, range target)
{
	vec2 pos = { 0 };
	while (ADD(pos, velocity), DRAG(velocity.x), velocity.y--, pos.y >= target.min.y)
		if (IN_RANGE(pos, target))
			return 1; // Hit!
	return 0;
}

static void solve(FILE *fp)
{
	int first = 0, second = 0;

	range target;
	fscanf(fp, "target area: x=%d..%d, y=%d..%d\n", &target.min.x, &target.max.x, &target.min.y,
	       &target.max.y);

	vec2 velocity;
	for (velocity.y = target.min.y; velocity.y <= -target.min.y; velocity.y++) {
		for (velocity.x = 0; velocity.x <= target.max.x; velocity.x++) {
			if (hits(velocity, target)) {
				second++;
				int height = velocity.y * (velocity.y + 1) / 2;
				if (height > first)
					first = height;
			}
		}
	}

	printf("%d\n%d\n", first, second);
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
