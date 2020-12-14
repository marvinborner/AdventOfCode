#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct mem_entry {
	long address;
	long value;
	struct mem_entry *next;
};

struct mem_map {
	struct mem_entry *head;
	struct mem_entry *tail;
};

struct mem_entry *get_entry(struct mem_map *mem_map, int address)
{
	if (!mem_map || !mem_map->head || !mem_map->tail)
		return NULL;

	struct mem_entry *iterator = mem_map->head;
	while (iterator) {
		if (iterator->address == address)
			return iterator;
		iterator = iterator->next;
	}
	return NULL;
}

void new_entry(struct mem_map *mem_map, long address, long value)
{
	/* printf("%lu: %lu\n", address, value); */
	if (!mem_map)
		return;

	struct mem_entry *override = NULL;
	if ((override = get_entry(mem_map, address))) {
		override->value = value;
		return;
	}

	struct mem_entry *new = malloc(sizeof(*new));
	new->address = address;
	new->value = value;
	new->next = NULL;

	if (mem_map->head && mem_map->tail) {
		mem_map->tail->next = new;
		mem_map->tail = new;
	} else {
		mem_map->head = new;
		mem_map->tail = mem_map->head;
	}
}

long count_doku(struct mem_map *mem_map)
{
	if (!mem_map || !mem_map->head || !mem_map->tail)
		return 0;

	long cnt = 0;
	struct mem_entry *iterator = mem_map->head;
	while (iterator) {
		cnt += iterator->value;
		iterator = iterator->next;
	}
	return cnt;
}

long part_one(FILE *fp)
{
	char *line = NULL;
	size_t len = 0;
	char mask[36] = { 0 };
	struct mem_map mem_map = { 0 };
	while (getline(&line, &len, fp) != -1) {
		if (line[0] == 'm' && line[1] == 'a') {
			sscanf(line, "mask = %s\n", &mask[0]);
		} else if (line[0] == 'm' && line[1] == 'e') {
			int address;
			long value;
			sscanf(line, "mem[%d] = %lu\n", &address, &value);
			for (char *p = mask; *p; p++) {
				long shift = 1ul << (35 - (p - mask));
				if (*p == '0')
					value &= ~shift;
				else if (*p == '1')
					value |= shift;
			}
			new_entry(&mem_map, address, value);
		}
	}

	return count_doku(&mem_map);
}

long part_two(FILE *fp)
{
	char *line = NULL;
	size_t len = 0;
	char mask[36] = { 0 };
	int floating_bits[64];
	struct mem_map mem_map = { 0 };
	while (getline(&line, &len, fp) != -1) {
		if (line[0] == 'm' && line[1] == 'a') {
			sscanf(line, "mask = %s\n", &mask[0]);
		} else if (line[0] == 'm' && line[1] == 'e') {
			long address = 0, value = 0;
			sscanf(line, "mem[%lu] = %lu\n", &address, &value);

			int floating = 0;
			for (int i = 0; i < 36; i++) {
				if (mask[i] == '1') {
					address |= 1L << (36 - i - 1);
				} else if (mask[i] == 'X') {
					floating_bits[floating] = i;
					floating++;
				}
			}

			long masked_addr = address;
			for (long perm = 0; perm < (1 << floating); ++perm) {
				long address = masked_addr;
				for (int j = 0; j < floating; ++j) {
					if (perm & (1L << j)) {
						address ^= (1L << (36 - floating_bits[j] - 1));
					}
				}
				new_entry(&mem_map, address, value);
			}
		}
	}

	return count_doku(&mem_map);
}

int main(int argc, char *argv[])
{
	FILE *fp = fopen("input", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	clock_t tic = clock();
	printf("%lu\n", part_one(fp));
	rewind(fp);
	printf("%lu\n", part_two(fp));
	clock_t toc = clock();
	printf("TIME: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	fclose(fp);
	return 0;
}
