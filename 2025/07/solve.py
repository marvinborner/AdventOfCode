#!/usr/bin/env python3

L = [list(l.strip()) for l in open("input").readlines()]


def part1():
    res = 0
    for y in range(len(L)):
        for x in range(len(L[y])):
            if L[y - 1][x] == "|" or L[y - 1][x] == "S":
                if L[y][x] == "^":
                    L[y][x - 1] = "|"
                    L[y][x + 1] = "|"
                    res += 1
                else:
                    L[y][x] = "|"
    print(res)


def part2():
    counts = [0 for l in L[0]]
    counts[L[0].index("S")] = 1
    for y in range(len(L)):
        for x in range(len(L[y])):
            if L[y][x] == "^":
                counts[x - 1] += counts[x]
                counts[x + 1] += counts[x]
                counts[x] = 0
    print(sum(counts))


part1()
part2()
