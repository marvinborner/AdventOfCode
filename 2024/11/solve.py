#!/bin/env python

stones = [int(d) for d in open("input").read().strip().split(" ")]

cache = {}


def solve(n, stone):
    if n == 0:
        return 1

    if (n, stone) in cache:
        return cache[(n, stone)]

    sstone = str(stone)
    if stone == 0:
        res = solve(n - 1, 1)
    elif len(sstone) % 2 == 0:
        left = solve(n - 1, int(sstone[: len(sstone) // 2]))
        right = solve(n - 1, int(sstone[len(sstone) // 2 :]))
        res = left + right
    else:
        res = solve(n - 1, stone * 2024)

    cache[(n, stone)] = res
    return res


part1 = 0
part2 = 0
for stone in stones:
    part1 += solve(25, stone)
    part2 += solve(75, stone)
print(part1, part2)
