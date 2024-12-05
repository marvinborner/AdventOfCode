#!/bin/env python


L = open("input").read().split("\n\n")
ordering = [[int(c) for c in l.split("|")] for l in L[0].split("\n")]
numss = [[int(c) for c in l.split(",")] for l in L[1].strip().split("\n")]


def check(nums):
    for i, a in enumerate(nums):
        for j, b in enumerate(nums[i:]):
            if [b, a] in ordering:
                return ((i, i + j), False)
    return (None, True)


# "bubble sort"
def fix(nums):
    while True:
        pos, ordered = check(nums)
        if ordered:
            return nums
        nums[pos[0]], nums[pos[1]] = nums[pos[1]], nums[pos[0]]


def solve():
    res1 = 0
    res2 = 0

    for nums in numss:
        _, ordered = check(nums)
        if ordered:
            res1 += nums[len(nums) // 2]
        else:
            fixed = fix(nums)
            res2 += fixed[len(fixed) // 2]

    print(res1)
    print(res2)


solve()
