#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part_one(char *data)
{
	// Strange parsing
	int note_earliest = 0, note_line = 0, note_service_index = 0;
	int note_in_service[128] = { 0 };
	for (char *p = data; *p; p++) {
		if (*p == '\n') {
			note_line++;
			continue;
		} else if (*p == 'x') {
			p++;
			continue;
		}

		if (!note_earliest && note_line == 0) {
			sscanf(p, "%d\n", &note_earliest);
		} else if (note_earliest && note_line == 1) {
			sscanf(p, "%d,", &note_in_service[note_service_index]);
			p += (int)(floor(log10(note_in_service[note_service_index])) + 1); // idk
			note_service_index++;
		}
	}

	// Strange loops
	for (int time = note_earliest;; time++) {
		for (int *bus = note_in_service; *bus != 0; bus++) {
			if (time % *bus == 0)
				return (time - note_earliest) * *bus;
		}
	}
}

int part_two(char *data)
{
	int res = 0;

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

	printf("%d\n", part_one(buf));
	printf("%d\n", part_two(buf));

	fclose(fp);
	return 0;
}
