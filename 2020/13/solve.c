#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

long part_two(char *data)
{
	int note_line = 0, note_service_index = 0;
	int note_in_service[128] = { 0 };
	for (char *p = data; *p; p++) {
		if (*p == '\n') {
			note_line++;
			continue;
		}

		if (note_line == 1) {
			if (*p == 'x') {
				note_in_service[note_service_index] = 0;
				p += 1;
			} else {
				sscanf(p, "%d,", &note_in_service[note_service_index]);
				p += (int)(floor(log10(note_in_service[note_service_index])) + 1);
			}
			note_service_index++;
		}
	}

	long pos = 0, offset = 1;
	for (int *bus = note_in_service; bus - note_in_service < note_service_index; bus++) {
		if (!*bus)
			continue;
		while ((pos + (bus - note_in_service)) % *bus)
			pos += offset;
		offset *= *bus;
	}

	return pos;
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
	printf("%d\n", part_one(buf));
	printf("%lu\n", part_two(buf));
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
