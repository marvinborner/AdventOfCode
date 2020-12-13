#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void normalize(char *data)
{
	for (char *p = data; *p; p++) {
		if (*p == '\n' && *(p + 1) == '\n') {
			*p = ' ';
			p++;
		} else if (*p == '\n') {
			*p = ' ';
		}
	}
}

char *valid[] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
char *valid_colors[] = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };

int part_one(char *data)
{
	int res = 0;

	int correct = 0;
	for (char *p = data; *p; p++) {
		if (*p == '\n') {
			if (correct == 7)
				res++;
			correct = 0;
			continue;
		}

		char key[4] = { 0 };
		char value[16] = { 0 };
		sscanf(p, "%3[^:]:%s ", key, value);

		for (int i = 0; i < sizeof(valid) / sizeof(valid[0]); ++i) {
			if (!strcmp(key, valid[i])) {
				correct++;
				break;
			}
		}

		p += 3 + strlen(value) + 1;
		if (*(p + 1) == '\0') {
			if (correct == 7)
				res++;
		}
	}

	return res;
}

#define EQ(a, b) (!strcmp((a), (b))) // String equality
#define BR(x) ((x) >= 1920 && (x) <= 2002) // Birth rule
#define IR(x) ((x) >= 2010 && (x) <= 2020) // Issue rule
#define ER(x) ((x) >= 2020 && (x) <= 2030) // Expiration rule
#define HR(x) ((x) >= 150 && (x) <= 193) // Height rule
#define CR(x)                                                                                      \
	(EQ(x, "amb") || EQ(x, "blu") || EQ(x, "brn") || EQ(x, "gry") || EQ(x, "grn") ||           \
	 EQ(x, "hzl") || EQ(x, "oth")) // Eye color rule
// BTW: I hate gotos
int part_two(char *data)
{
	int res = 0;

	int correct = 0;
	for (char *p = data; *p; p++) {
		if (*p == '\n') {
			if (correct == 7)
				res++;
			correct = 0;
			continue;
		}
		char key[4] = { 0 };
		char value[16] = { 0 };
		sscanf(p, "%3[^:]:%s ", key, value);

		// General value verification/parsing
		int y = 0;
		if (EQ(key, "byr") || EQ(key, "iyr") || EQ(key, "eyr")) {
			if (!sscanf(value, "%4d", &y))
				goto invalid;
		} else if (EQ(key, "hgt")) {
			char last = value[strlen(value) - 1];
			if (last == 'm') {
				sscanf(value, "%dcm", &y);
			} else if (last == 'n') {
				sscanf(value, "%din", &y);
				y = (int)roundf(((float)y * 2.54)); // lol
			} else {
				goto invalid;
			}
		} else if (EQ(key, "hcl") && (strlen(value) != 7 || !sscanf(value, "#%6x", &y))) {
			goto invalid;
		} else if (EQ(key, "ecl")) {
			char c[4];
			if (!sscanf(value, "%3s", c) || !CR(c))
				goto invalid;
		} else if (EQ(key, "pid")) {
			if (!sscanf(value, "%9d", &y))
				goto invalid;
		}

		// Number range verification
		if (EQ(key, "byr") && !BR(y))
			goto invalid;
		else if (EQ(key, "iyr") && !IR(y))
			goto invalid;
		else if (EQ(key, "eyr") && !ER(y))
			goto invalid;
		else if (EQ(key, "hgt") && !HR(y)) {
			goto invalid;
		}

		for (int i = 0; i < sizeof(valid) / sizeof(valid[0]); ++i) {
			if (!strcmp(key, valid[i])) {
				correct++;
				break;
			}
		}

		goto next;

	invalid:
		/* printf("Invalid: %s:%s (y=%d)\n", key, value, y); */
		correct = -42; // Awesome fix!
	next:
		p += 3 + strlen(value) + 1;
		if (*(p + 1) == '\0') {
			if (correct == 7)
				res++;
		}
	}

	return res;
}

#define SIZE 20000
int main(int argc, char *argv[])
{
	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);
	char buf[SIZE] = { 0 };
	fread(buf, SIZE, 1, fp);

	clock_t tic = clock();
	normalize(buf);
	printf("%d\n", part_one(buf));
	printf("%d\n", part_two(buf));
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
