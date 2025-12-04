#!/bin/env python

L = [[" "] + list(l.strip()) + [" "] for l in open("input").readlines()]
buf = list(map(lambda _: " ", L[0]))
L.insert(0, buf)
L.append(buf)


def removable(mp, x, y):
    return (
        mp[y][x] == "@"
        and (mp[y - 1][x - 1] == "@")
        + (mp[y - 1][x] == "@")
        + (mp[y - 1][x + 1] == "@")
        + (mp[y][x - 1] == "@")
        + (mp[y][x + 1] == "@")
        + (mp[y + 1][x - 1] == "@")
        + (mp[y + 1][x] == "@")
        + (mp[y + 1][x + 1] == "@")
        < 4
    )


def part1():
    res = 0
    for y in range(len(L)):
        for x in range(len(L[y])):
            if removable(L, x, y):
                res += 1
    print(res)


def part2():
    res = 0
    while True:
        cur = res
        for y in range(len(L)):
            for x in range(len(L[y])):
                if removable(L, x, y):
                    L[y][x] = "."
                    cur += 1
        if cur == res:
            break
        res = cur
    print(res)


part1()
part2()
