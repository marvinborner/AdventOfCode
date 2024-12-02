#!/bin/env python


L = [[int(i) for i in l.split()] for l in open("input").readlines()]


def safe(l):
    diffs = [l[i + 1] - l[i] for i in range(len(l) - 1)]
    if max(diffs) <= 3 and min(diffs) >= 1 and all(x > 0 for x in diffs):
        return 1
    elif min(diffs) >= -3 and max(diffs) <= -1 and all(x < 0 for x in diffs):
        return 1
    else:
        return 0


def part1():
    res = 0

    for l in L:
        res += safe(l)

    print(res)


def part2():
    res = 0

    for l in L:
        for s in [l[:i] + l[i + 1 :] for i in range(len(l))]:
            if safe(s):
                res += 1
                break

    print(res)


part1()
part2()
