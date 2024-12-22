#!/bin/env python3

L = [int(l.strip()) for l in open("input").readlines()]


def evolve(n):
    n ^= n * 64
    n %= 16777216

    n ^= n // 32
    n %= 16777216

    n ^= n * 2048
    n %= 16777216

    return n


def part1(n):
    for i in range(2000):
        n = evolve(n)
    return n


def part2():
    M = {}
    for n in L:
        diffs = []
        vals = [0]
        for i in range(2000):
            n = evolve(n)
            s = n % 10
            diffs.append(s - vals[-1])
            vals.append(s)

        s = set()
        for i in range(4, len(vals)):
            r = tuple(diffs[i - 4 : i])
            if r not in s:
                if r in M:
                    M[r] += vals[i]
                else:
                    M[r] = vals[i]
                s.add(r)
    return M[max(M, key=M.get)]


print(sum(part1(n) for n in L))
print(part2())
