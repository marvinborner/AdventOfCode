#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part_one()
{
	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	int res = 0;

	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		(void)read;
		int low, high, cnt = 0;
		char ch;
		char str[256];
		sscanf(line, "%d-%d %c: %s\n", &low, &high, &ch, &str[0]);
		for (int i = 0; i < strlen(str); i++) {
			if (str[i] == ch) {
				cnt++;
			}
		}
		if (cnt >= low && cnt <= high)
			res++;
	}

	fclose(fp);

	return res;
}

int part_two()
{
	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	int res = 0;

	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		(void)read;
		int low, high, cnt = 0;
		char ch, first, second;
		char str[256];
		sscanf(line, "%d-%d %c: %s\n", &low, &high, &ch, &str[0]);
		first = str[low - 1];
		second = str[high - 1];
		if (first == ch && second != ch || first != ch && second == ch)
			res++;
	}

	fclose(fp);

	return res;
}

int main(int argc, char *argv[])
{
	printf("%d\n", part_one());
	printf("%d\n", part_two());
	return 0;
}
