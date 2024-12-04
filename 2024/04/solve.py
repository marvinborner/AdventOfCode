#!/bin/env python


L = [l.strip() for l in open("input").readlines()]


# AAAAAAAAAAAAAAAAAH PYTHON WHY DO YOU SUPPORT -1 INDEX
# THIS COST ME 20 MINUTES
def get(l, idx):
    if idx >= len(l) or idx < 0:
        return "."
    return l[idx]


def part1():
    res = 0

    for y in range(len(L)):
        for x in range(len(L[y])):
            # horizontal
            if (
                get(get(L, y), x) == "X"
                and get(get(L, y), x + 1) == "M"
                and get(get(L, y), x + 2) == "A"
                and get(get(L, y), x + 3) == "S"
            ):
                res += 1

            # horizontal inversed
            if (
                get(get(L, y), x) == "S"
                and get(get(L, y), x + 1) == "A"
                and get(get(L, y), x + 2) == "M"
                and get(get(L, y), x + 3) == "X"
            ):
                res += 1

            # diagonal right
            if (
                get(get(L, y), x) == "X"
                and get(get(L, y + 1), x + 1) == "M"
                and get(get(L, y + 2), x + 2) == "A"
                and get(get(L, y + 3), x + 3) == "S"
            ):
                res += 1

            # diagonal right inversed
            if (
                get(get(L, y), x) == "S"
                and get(get(L, y + 1), x + 1) == "A"
                and get(get(L, y + 2), x + 2) == "M"
                and get(get(L, y + 3), x + 3) == "X"
            ):
                res += 1

            # vertical
            if (
                get(get(L, y), x) == "X"
                and get(get(L, y + 1), x) == "M"
                and get(get(L, y + 2), x) == "A"
                and get(get(L, y + 3), x) == "S"
            ):
                res += 1

            # vertical inversed
            if (
                get(get(L, y), x) == "S"
                and get(get(L, y + 1), x) == "A"
                and get(get(L, y + 2), x) == "M"
                and get(get(L, y + 3), x) == "X"
            ):
                res += 1

            # diagonal left
            if (
                get(get(L, y), x) == "X"
                and get(get(L, y + 1), x - 1) == "M"
                and get(get(L, y + 2), x - 2) == "A"
                and get(get(L, y + 3), x - 3) == "S"
            ):
                res += 1

            # diagonal left inversed
            if (
                get(get(L, y), x) == "S"
                and get(get(L, y + 1), x - 1) == "A"
                and get(get(L, y + 2), x - 2) == "M"
                and get(get(L, y + 3), x - 3) == "X"
            ):
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
