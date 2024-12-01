#!/bin/env python

# L = open("input").readlines()
L = [
    [int(i) for i in l.strip().split("   ")] for l in open("input").readlines()
]
# L = [int(l.strip()) for l in open("input").readlines()]


def part1():
    res = 0
    left = [l[0] for l in L]
    right = [l[1] for l in L]
    while left:
        left_min = min(range(len(left)), key=left.__getitem__)
        right_min = min(range(len(right)), key=right.__getitem__)
        res += abs(left[left_min] - right[right_min])
        del left[left_min]
        del right[right_min]
    print(res)


def part2():
    res = 0
    left = [l[0] for l in L]
    right = [l[1] for l in L]
    for i, l in enumerate(left):
        res += l * right.count(l)
    print(res)


part1()
part2()
