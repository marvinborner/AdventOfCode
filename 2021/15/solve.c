#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COUNT(a) ((int)(sizeof(a) / sizeof 0 [a]))

#define WHOLE                                                                                      \
	fseek(fp, 0, SEEK_END);                                                                    \
	long fsize = ftell(fp);                                                                    \
	fseek(fp, 0, SEEK_SET);                                                                    \
	char *data = malloc(fsize + 1);                                                            \
	fread(data, 1, fsize, fp);                                                                 \
	data[fsize] = 0;

struct node {
	int x, y;
	int risk;
};

// prioritized queue
struct queue {
	struct node *heap;
	int size, max;
};

static void pop(struct queue *queue, struct node *out)
{
	if (queue->size <= 0) {
		fprintf(stderr, "Can't pop null node\n");
		exit(1);
	}

	*out = queue->heap[0];
	queue->heap[0] = queue->heap[--queue->size];

	for (int i = 0, curr = 0;; curr = i) {
		int child = (curr << 1) + 1;
		if (child < queue->size && queue->heap[child].risk < queue->heap[curr].risk)
			i = child;
		child++;
		if (child < queue->size && queue->heap[child].risk < queue->heap[i].risk)
			i = child;
		if (i == curr)
			break;
		struct node temp = queue->heap[curr];
		queue->heap[curr] = queue->heap[i];
		queue->heap[i] = temp;
	}
}

static void push(struct queue *queue, int x, int y, int risk)
{
	if (queue->size >= queue->max) {
		fprintf(stderr, "Queue size too big\n");
		exit(1);
	}

	queue->heap[queue->size].x = x;
	queue->heap[queue->size].y = y;
	queue->heap[queue->size].risk = risk;
	int p = 0;
	for (int i = queue->size++; i > 0; i = p) {
		p = (i - 1) >> 1;
		if (queue->heap[p].risk <= queue->heap[i].risk)
			break;
		// Swap
		struct node temp = queue->heap[i];
		queue->heap[i] = queue->heap[p];
		queue->heap[p] = temp;
	}
}

static struct queue *create(int size)
{
	struct queue *queue = malloc(sizeof(*queue));
	queue->heap = malloc(sizeof(*queue->heap) * size);
	queue->size = 0;
	queue->max = size;
	return queue;
}

#define SIZE 100
#define GET(x, y) (data[(y) * (SIZE + 1) + (x)] - '0')
static int part_one(FILE *fp)
{
	int risk = 0;

	WHOLE;

	int visited[SIZE][SIZE] = { 0 };

	struct queue *queue = create(1000);
	push(queue, 0, 0, 0);

	while (1) {
		struct node node;
		pop(queue, &node);
		int x = node.x;
		int y = node.y;
		risk = node.risk;

		if (visited[x][y])
			continue;
		if (x == SIZE - 1 && y == SIZE - 1)
			break;

		visited[x][y] = 1;
		if (x + 1 < SIZE && !visited[x + 1][y])
			push(queue, x + 1, y, risk + GET(x + 1, y));
		if (y + 1 < SIZE && !visited[x][y + 1])
			push(queue, x, y + 1, risk + GET(x, y + 1));
		if (x - 1 >= 0 && !visited[x - 1][y])
			push(queue, x - 1, y, risk + GET(x - 1, y));
		if (y - 1 >= 0 && !visited[x][y - 1])
			push(queue, x, y - 1, risk + GET(x, y - 1));
	}

	free(data);
	free(queue->heap);
	free(queue);

	return risk;
}

#define SIZE2 (SIZE * 5)
#define GET2(x, y)                                                                                 \
	(((data[((y) % SIZE) * (SIZE + 1) + ((x) % SIZE)] - '0' + ((x) / SIZE + (y) / SIZE)) -     \
	  1) % 9 +                                                                                 \
	 1)
static int part_two(FILE *fp)
{
	int risk = 0;

	WHOLE;

	int visited[SIZE2][SIZE2] = { 0 };

	struct queue *queue = create(10000);
	push(queue, 0, 0, 0);

	while (1) {
		struct node node;
		pop(queue, &node);
		int x = node.x;
		int y = node.y;
		risk = node.risk;

		if (visited[x][y])
			continue;
		if (x == SIZE2 - 1 && y == SIZE2 - 1)
			break;

		visited[x][y] = 1;
		if (x + 1 < SIZE2 && !visited[x + 1][y])
			push(queue, x + 1, y, risk + GET2(x + 1, y));
		if (y + 1 < SIZE2 && !visited[x][y + 1])
			push(queue, x, y + 1, risk + GET2(x, y + 1));
		if (x - 1 >= 0 && !visited[x - 1][y])
			push(queue, x - 1, y, risk + GET2(x - 1, y));
		if (y - 1 >= 0 && !visited[x][y - 1])
			push(queue, x, y - 1, risk + GET2(x, y - 1));
	}

	free(data);
	free(queue->heap);
	free(queue);

	return risk;
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
	printf("%d\n", part_two(fp));
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
