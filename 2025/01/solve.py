#!/bin/env python

L = [(-1 if l[0] == "L" else 1) * int(l[1:]) for l in open("input").readlines()]
L.insert(0, 50)


def part1():
    res = 0
    s = 0
    for l in L:
        s += l
        if s % 100 == 0:
            res += 1
    print(res)


def part2():
    res = 0
    s = 0
    for l in L:
        for i in range(abs(l)):
            s += -1 if l < 0 else 1
            if s % 100 == 0:
                res += 1
    print(res)


part1()
part2()
