#include "../../lib/uthash.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct mem {
	long address;
	long value;
	UT_hash_handle hh;
};

void new_entry(struct mem **mem, long address, long value)
{
	struct mem *addr;
	HASH_FIND(hh, *mem, &address, sizeof(address), addr);
	if (addr == NULL) {
		addr = malloc(sizeof(*addr));
		addr->address = address;
		HASH_ADD(hh, *mem, address, sizeof(address), addr);
	}
	addr->value = value;
}

long part_one(FILE *fp)
{
	char *line = NULL;
	size_t len = 0;
	char mask[36] = { 0 };
	struct mem *mem = NULL;
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
			new_entry(&mem, address, value);
		}
	}

	long sum = 0;
	struct mem *addr, *tmp;
	HASH_ITER(hh, mem, addr, tmp)
	{
		sum += addr->value;
		HASH_DEL(mem, addr);
		free(addr);
	}

	return sum;
}

long part_two(FILE *fp)
{
	char *line = NULL;
	size_t len = 0;
	char mask[36] = { 0 };
	int floating_bits[64];
	struct mem *mem = NULL;
	while (getline(&line, &len, fp) != -1) {
		if (line[0] == 'm' && line[1] == 'a') {
			sscanf(line, "mask = %s\n", &mask[0]);
		} else if (line[0] == 'm' && line[1] == 'e') {
			long address = 0, value = 0;
			sscanf(line, "mem[%lu] = %lu\n", &address, &value);

			int floating = 0;
			for (int i = 0; i < 36; i++) {
				if (mask[i] == '1') {
					address |= 1ul << (36 - i - 1);
				} else if (mask[i] == 'X') {
					floating_bits[floating] = i;
					floating++;
				}
			}

			long masked_addr = address;
			for (long perm = 0; perm < (1 << floating); ++perm) {
				long address = masked_addr;
				for (int j = 0; j < floating; j++)
					if (perm & (1ul << j))
						address ^= (1ul << (36 - floating_bits[j] - 1));
				new_entry(&mem, address, value);
			}
		}
	}

	long sum = 0;
	struct mem *addr, *tmp;
	HASH_ITER(hh, mem, addr, tmp)
	{
		sum += addr->value;
		HASH_DEL(mem, addr);
		free(addr);
	}
	return sum;
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
