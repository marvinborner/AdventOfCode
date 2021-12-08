#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COUNT(a) ((int)(sizeof(a) / sizeof 0 [a]))

#define FORLINE                                                                                    \
	char *line = NULL;                                                                         \
	size_t len = 0;                                                                            \
	while (getline(&line, &len, fp) != EOF)
#define FREELINE                                                                                   \
	if (line)                                                                                  \
	free(line)

enum segments {
	SEG0 = 6,
	SEG1 = 2,
	SEG2 = 5,
	SEG3 = 5,
	SEG4 = 4,
	SEG5 = 5,
	SEG6 = 6,
	SEG7 = 3,
	SEG8 = 7,
	SEG9 = 6,
};
#define SEG(x) (SEG##x)
#define UNIQSEG(x) (x == SEG1 ? 1 : x == SEG4 ? 4 : x == SEG7 ? 7 : x == SEG8 ? 8 : 0)

static int part_one(FILE *fp)
{
	int res = 0;

	FORLINE
	{
		char *p = line;
		while (*p != '|')
			p++;
		p += 2; // space after |

		for (int i = 0; i < 4; i++) {
			int size = 0;
			while (*p != ' ' && *p != '\n') {
				size++;
				p++;
			}
			p++; // Space after end

			if (UNIQSEG(size))
				res++;
		}
	}
	FREELINE;

	return res;
}

// Longest function ever INCOMING!!
static int part_two(FILE *fp)
{
	int res = 0;

	FORLINE
	{
		char *p = line;

		// Parse input
		struct input {
			char seq[8];
			int len;
			int num;
		};
		struct input input[10] = { 0 };

		for (int i = 0; i < COUNT(input); i++) {
			sscanf(p, "%[^ ] %n", input[i].seq, &input[i].len);
			p += input[i].len;
			input[i].len--;
			input[i].num = -1;
		}

		while (*p != '|')
			p++;
		p += 2; // Space after |

		// Solve input
		struct input *found[10] = { 0 };
		int count = 0;

		// First look for unique segments
		for (int i = 0; i < COUNT(input); i++) {
			int uniq = UNIQSEG(input[i].len);
			if (uniq) {
				//printf("found %d: %s\n", uniq, input[i].seq);
				found[uniq] = &input[i];
				input[i].num = uniq;
				count++;
			}
		}

		// Now the others based on the uniques
		int i = 0;
		while (count < COUNT(input)) {
			if (++i == COUNT(input))
				i = 0;

			if (input[i].num >= 0)
				continue;

			if (input[i].len == 6) {
				if (!found[6]) {
					int valid = 0;
					for (int j = 0; j < input[i].len; j++)
						for (int k = 0; k < found[1]->len; k++)
							if (input[i].seq[j] != found[1]->seq[k])
								valid++;
							else
								valid--;
					if (valid == 10) {
						//printf("found 6: %s\n", input[i].seq);
						found[6] = &input[i];
						input[i].num = 6;
						count++;
						continue;
					}
				}

				if (!found[9]) {
					int valid = 0;
					for (int j = 0; j < input[i].len; j++) {
						for (int k = 0; k < found[4]->len; k++) {
							if (input[i].seq[j] == found[4]->seq[k]) {
								valid++;
								break;
							}
						}
						if (valid == found[4]->len) {
							//printf("found 9: %s\n", input[i].seq);
							found[9] = &input[i];
							input[i].num = 9;
							count++;
							valid = -1;
							break;
						}
					}
					if (valid < 0)
						continue;
				}

				// You only need to solve 2/3
				if (found[6] && found[9]) {
					//printf("found 0: %s\n", input[i].seq);
					found[0] = &input[i];
					input[i].num = 0;
					count++;
				}
			} else if (input[i].len == 5) {
				if (!found[3]) {
					int valid = 0;
					for (int j = 0; j < input[i].len; j++) {
						for (int k = 0; k < found[1]->len; k++) {
							if (input[i].seq[j] == found[1]->seq[k]) {
								valid++;
								break;
							}
						}
						if (valid == found[1]->len) {
							//printf("found 3: %s\n", input[i].seq);
							found[3] = &input[i];
							input[i].num = 3;
							count++;
							valid = -1;
							break;
						}
					}
					if (valid < 0)
						continue;
				}

				// 5 is basically 6
				if (!found[5] && found[6]) {
					int valid = 0;
					for (int j = 0; j < input[i].len; j++) {
						for (int k = 0; k < found[6]->len; k++) {
							if (input[i].seq[j] == found[6]->seq[k]) {
								valid++;
								break;
							}
						}
						if (valid == found[6]->len - 1) {
							//printf("found 5: %s\n", input[i].seq);
							found[5] = &input[i];
							input[i].num = 5;
							count++;
							valid = -1;
							break;
						}
					}
					if (valid < 0)
						continue;
				}

				// You only need to solve 2/3
				if (found[5] && found[6]) {
					//printf("found 2: %s\n", input[i].seq);
					found[2] = &input[i];
					input[i].num = 2;
					count++;
				}
			} else {
				fprintf(stderr, "Huh: %d\n", input[i].len);
			}
		}

		// Parse output
		struct output {
			char seq[8];
			int len;
		};
		struct output output[4] = { 0 };

		for (i = 0; i < COUNT(output); i++) {
			sscanf(p, "%[^ ] %n", output[i].seq, &output[i].len);
			p += output[i].len;
			output[i].len--;

			for (int j = 0; j < COUNT(found); j++) {
				int valid = 0;

				if (output[i].len == found[j]->len) {
					for (int k = 0; k < output[i].len; k++) {
						for (int l = 0; l < found[j]->len; l++) {
							if (output[i].seq[k] == found[j]->seq[l])
								valid++;
						}
					}

					if (valid == output[i].len) {
						res += j * (i == 3 ? 1 :
							    i == 2 ? 10 :
							    i == 1 ? 100 :
							    i == 0 ? 1000 :
									   0);
						continue;
					}
				}
			}
		}
	}
	FREELINE;

	return res;
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
