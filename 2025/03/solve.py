#!/bin/env python

banks = [[int(x) for x in list(l.strip())] for l in open("input").readlines()]


def part1():
    res = 0
    for bank in banks:
        max1 = max(bank[:-1])
        max2 = max(bank[bank.index(max1) + 1 :])
        num = str(max1) + str(max2)
        res += int(num)
    print(res)


def part2():
    res = 0
    for bank in banks:
        maxs = ""
        start = 0
        for i in range(12, 0, -1):
            m = max(bank[start : len(bank) - i + 1])
            start += bank[start:].index(m) + 1
            maxs += str(m)
        res += int(maxs)
    print(res)


part1()
part2()
