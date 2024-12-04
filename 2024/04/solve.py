#!/bin/env python


L = [l.strip() for l in open("input").readlines()]


# AAAAAAAAAAAAAAAAAH PYTHON WHY DO YOU SUPPORT -1 INDEX
# THIS COST ME 20 MINUTES
def get(l, idx):
    if idx >= len(l) or idx < 0:
        return "."
    return l[idx]


def scan(what, y, x, yshift, xshift):
    return (
        get(get(L, y), x) == what[0]
        and get(get(L, y + 1 * yshift), x + 1 * xshift) == what[1]
        and get(get(L, y + 2 * yshift), x + 2 * xshift) == what[2]
        and get(get(L, y + 3 * yshift), x + 3 * xshift) == what[3]
    )


def part1():
    res = 0

    for y in range(len(L)):
        for x in range(len(L[y])):
            # horizontal
            if scan("XMAS", y, x, 0, 1):
                res += 1

            # horizontal inversed
            if scan("SAMX", y, x, 0, 1):
                res += 1

            # diagonal right
            if scan("XMAS", y, x, 1, 1):
                res += 1

            # diagonal right inversed
            if scan("SAMX", y, x, 1, 1):
                res += 1

            # vertical
            if scan("XMAS", y, x, 1, 0):
                res += 1

            # vertical inversed
            if scan("SAMX", y, x, 1, 0):
                res += 1

            # diagonal left
            if scan("XMAS", y, x, 1, -1):
                res += 1

            # diagonal left inversed
            if scan("SAMX", y, x, 1, -1):
                res += 1
    print(res)


def part2():
    res = 0

    for y in range(len(L)):
        for x in range(len(L[y])):
            if (
                (
                    get(get(L, y), x) == "S"
                    and get(get(L, y + 1), x + 1) == "A"
                    and get(get(L, y + 2), x + 2) == "M"
                )
                or (
                    get(get(L, y), x) == "M"
                    and get(get(L, y + 1), x + 1) == "A"
                    and get(get(L, y + 2), x + 2) == "S"
                )
            ) and (
                (
                    get(get(L, y), x + 2) == "S"
                    and get(get(L, y + 1), x + 1) == "A"
                    and get(get(L, y + 2), x) == "M"
                )
                or (
                    get(get(L, y), x + 2) == "M"
                    and get(get(L, y + 1), x + 1) == "A"
                    and get(get(L, y + 2), x) == "S"
                )
            ):
                res += 1
    print(res)


part1()
part2()
