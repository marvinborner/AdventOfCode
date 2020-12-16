#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct rule {
	int low1;
	int high1;
	int low2;
	int high2;
};

int solve(FILE *fp)
{
	// Part one
	char *line = NULL;
	size_t len = 0;
	int paragraph = 0;
	char name[64];
	char valid[256][128];
	int invalid[4096] = { 0 };
	struct rule rules[64] = { 0 };
	int rule_cnt = 0, invalid_cnt = 0, valid_cnt = 0;
	while (getline(&line, &len, fp) != -1) {
		if (line[0] == '\n') {
			paragraph++;
			continue;
		}
		if (paragraph == 0) {
			int low1, high1, low2, high2;
			sscanf(line, "%[^:]: %u-%u or %u-%u\n", name, &low1, &high1, &low2, &high2);
			struct rule rule = {
				.low1 = low1, .high1 = high1, .low2 = low2, .high2 = high2
			};
			rules[rule_cnt++] = rule;
		} else if (paragraph == 2) {
			if (line[0] == 'n')
				continue;

			int num;
			int bytes_now, bytes_consumed = 0;

			int invalid_ticket = 0;
			while (sscanf(line + bytes_consumed, "%d,%n", &num, &bytes_now) > 0) {
				int inc = 0;
				for (int i = 0; i < rule_cnt; i++) {
					struct rule rule = rules[i];
					if ((num >= rule.low1 && num <= rule.high1) ||
					    (num >= rule.low2 && num <= rule.high2)) {
						inc = 0;
						break;
					} else {
						inc = num;
					}
				}
				if (inc) {
					invalid[invalid_cnt++] = num;
					invalid_ticket = 1;
				}

				bytes_consumed += bytes_now;
			}
			if (!invalid_ticket)
				strcpy(valid[valid_cnt++], line);
		}
	}

	int cnt = 0;
	for (int i = 0; i < invalid_cnt; i++) {
		cnt += invalid[i];
	}
	printf("%d\n", cnt);

	// Part two
	for (int i = 0; i < valid_cnt; i++) {
		//printf("%s", valid[i]);
	}

	return 0;
}

int main(int argc, char *argv[])
{
	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	clock_t tic = clock();
	printf("%d\n", solve(fp));
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
