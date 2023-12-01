#!/bin/env python

# i don't like regex

L = open("input").readlines()

def part1():
    print(sum((n := list(filter(lambda x: x.isdigit(), l.strip())), int(n[0] + n[-1]))[1] for l in L))


def part2():
    u = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
    print(sum((i := [int(p[0]) if p[0].isdigit() else u.index(p[: len(n)]) + 1 for p in r for n in u if p.startswith(n) or p[0].isdigit()], i[0] * 10 + i[-1])[1] for r in [[l[i : i + 7] for i in range(len(l))] for l in L]))


part1()
part2()
