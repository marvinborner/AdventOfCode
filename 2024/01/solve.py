#!/bin/env python

from collections import Counter

L = [
    [int(i) for i in l.strip().split("   ")] for l in open("input").readlines()
]


def part1():
    res = 0
    left = sorted(l[0] for l in L)
    right = sorted(l[1] for l in L)
    for i in range(len(left)):
        res += abs(left[i] - right[i])
    print(res)


def part2():
    res = 0
    left = [l[0] for l in L]
    right = [l[1] for l in L]
    c = Counter(right)
    print(sum(l * c[l] for l in left))


part1()
part2()
