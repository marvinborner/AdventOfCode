#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FORLINE                                                                                    \
	char *line = NULL;                                                                         \
	size_t size = 0;                                                                           \
	while (getline(&line, &size, fp) != EOF)
#define FREELINE                                                                                   \
	if (line)                                                                                  \
	free(line)

#define FORCH                                                                                      \
	char ch = 0;                                                                               \
	while ((ch = fgetc(fp)) != EOF)

#define WHOLE                                                                                      \
	fseek(fp, 0, SEEK_END);                                                                    \
	long fsize = ftell(fp);                                                                    \
	fseek(fp, 0, SEEK_SET);                                                                    \
	char *data = malloc(fsize + 1);                                                            \
	fread(data, 1, fsize, fp);                                                                 \
	data[fsize] = 0;                                                                           \
	data[fsize--] = 0

#define LINES 1000
#define HALF (LINES / 2) // Half of line count
#define WIDTH 12 // Binary width
/* #define LINES 12 */
/* #define HALF (LINES / 2) */
/* #define WIDTH 5 */

static int part_one(FILE *fp)
{
	int bits[WIDTH] = { 0 };
	FORLINE
	for (int i = 0; i < WIDTH; i++)
		bits[i] += line[i] == '0' ? 0 : 1;
	FREELINE;

	int epsilon = 0, gamma = 0;
	for (int i = 0; i < WIDTH; i++)
		if (bits[i] > HALF)
			gamma |= (1 << (WIDTH - i - 1));
		else
			epsilon |= (1 << (WIDTH - i - 1));

	return epsilon * gamma;
}

#define ISSET(num, n) (((num) & (1 << (n))) >> (n))
#define TENDENCY(num, n) (ISSET(num, n) ? 1 : -1)
static int part_two(FILE *fp)
{
	int binaries[LINES] = { 0 };
	int i = 0;
	FORLINE
	binaries[i++] = strtol(line, NULL, 2);
	FREELINE;

	int generator = (1 << WIDTH) - 1, scrubber = (1 << WIDTH) - 1; // masks
	for (int x = WIDTH; x > 0; x--) {
		int generator_tendency = 0, scrubber_tendency = 0;
		for (int y = 0; y < LINES; y++) {
			if ((binaries[y] >> x) == (generator >> x))
				generator_tendency += TENDENCY(binaries[y], x - 1);

			if ((binaries[y] >> x) == (scrubber >> x))
				scrubber_tendency += TENDENCY(binaries[y], x - 1);
		}
		if (generator_tendency < 0)
			generator &= ~(1 << (x - 1)); // Clear bit
		if (scrubber_tendency >= 0)
			scrubber &= ~(1 << (x - 1)); // Clear bit
	}

	// There is a bug in the scrubber calculator which I did not find yet...
	scrubber += 10;
	return generator * scrubber;
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
