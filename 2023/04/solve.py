import re

L = [re.sub(" +", " ", l.strip()) for l in open("input").readlines()]


def solve1():
    res = 0
    for l in L:
        ls = l.split(": ")
        card = ls[0]
        winning, have = [
            list(map(int, a.split(" "))) for a in ls[1].split(" | ")
        ]
        s = 0
        i = True
        for x in have:
            if x in winning:
                s = s + 1 if i else s * 2
                i = False
        res += s
    print(res)


def solve2():
    res = 0
    dup = [1] * len(L)
    for i, l in enumerate(L):
        ls = l.split(": ")
        card = ls[0]
        winning, have = [
            list(map(int, a.split(" "))) for a in ls[1].split(" | ")
        ]
        s = 0
        for x in have:
            if x in winning:
                s += 1
        for j in range(i + 1, i + s + 1):
            dup[j] += dup[i]
    print(sum(dup))


solve1()
solve2()
