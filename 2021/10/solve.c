#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FORLINE                                                                                    \
	char *line = NULL;                                                                         \
	size_t len = 0;                                                                            \
	while (getline(&line, &len, fp) != EOF)
#define FREELINE                                                                                   \
	if (line)                                                                                  \
	free(line)

enum bracket {
	NONE,
	ROUND,
	SQUARE,
	CURLY,
	ANGLE,
	INVALID,
};

enum side {
	HUH,
	LEFT,
	RIGHT,
};

static const int syntax_points[] = { 0, 3, 57, 1197, 25137, 0 };
static const int complete_points[] = { 0, 1, 2, 3, 4, 0 };

#define LBRACKET(ch)                                                                               \
	((ch) == '(' ? ROUND :                                                                     \
	 (ch) == '[' ? SQUARE :                                                                    \
	 (ch) == '{' ? CURLY :                                                                     \
	 (ch) == '<' ? ANGLE :                                                                     \
			     INVALID)
#define RBRACKET(ch)                                                                               \
	((ch) == ')' ? ROUND :                                                                     \
	 (ch) == ']' ? SQUARE :                                                                    \
	 (ch) == '}' ? CURLY :                                                                     \
	 (ch) == '>' ? ANGLE :                                                                     \
			     INVALID)

#define RORL(ch)                                                                                   \
	(((ch) == '(' || (ch) == '[' || (ch) == '{' || (ch) == '<') ? LEFT :                       \
	 ((ch) == ')' || (ch) == ']' || (ch) == '}' || (ch) == '>') ? RIGHT :                      \
									    HUH)

/**
 * TODO: syntax() and complete() can probably be merged together
 */

static char *syntax(char *p, char **failure)
{
	if (*p == '\n' || !*p || *failure)
		return p;

	enum side rorl = RORL(*p);
	if (rorl == LEFT) {
		char *close = syntax(p + 1, failure);
		if (*failure)
			return p;
		if (RBRACKET(*close) == LBRACKET(*p))
			return syntax(close + 1, failure);
		*failure = close;
		return p;
	} else if (rorl == RIGHT) {
		return p;
	}

	fprintf(stderr, "Unknown '%c'\n", *p);
	return 0;
}

static char *complete(char *p, long *score)
{
	if (*p == '\n' || !*p)
		return p;

	enum side rorl = RORL(*p);
	if (rorl == LEFT) {
		char *close = complete(p + 1, score);
		if (RBRACKET(*close) == LBRACKET(*p))
			return complete(close + 1, score);
		*score *= 5;
		*score += complete_points[LBRACKET(*p)];
		return p;
	} else if (rorl == RIGHT) {
		return p;
	}

	fprintf(stderr, "Unknown '%c'\n", *p);
	return 0;
}

// For qsort
static int compare(const void *a, const void *b)
{
	if (*(const long *)a < *(const long *)b)
		return -1;
	return *(const long *)a > *(const long *)b;
}

static void solve(FILE *fp)
{
	int first = 0;

	long scores[100] = { 0 };
	int score_cnt = 0;

	FORLINE
	{
		char *failure = 0;
		syntax(line, &failure);
		if (failure && *failure && *failure != '\n') {
			first += syntax_points[RBRACKET(*failure)];
		} else {
			long points = 0;
			complete(line, &points);
			scores[score_cnt++] = points;
		}
	}
	FREELINE;

	qsort(scores, score_cnt, sizeof(scores[0]), compare);

	printf("%d\n%lu\n", first, scores[score_cnt / 2]);
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
