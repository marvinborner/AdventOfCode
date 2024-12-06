#!/bin/env python


L = [list(l.strip()) for l in open("input").readlines()]

UP = 0
RIGHT = 1
DOWN = 2
LEFT = 3

YLEN = len(L)
XLEN = len(L[0])


def put(y, x, c):
    L[y][x] = c


def get(y, x):
    if 0 <= y < YLEN and 0 <= x < XLEN:
        return L[y][x]
    return "#"


def start():
    for y, row in enumerate(L):
        for x, col in enumerate(row):
            if col == "^":
                L[y][x] = "."
                return y, x


def move(y, x, d):
    if d == UP and get(y - 1, x) == ".":
        return (y - 1, x, UP)
    if d == RIGHT and get(y, x + 1) == ".":
        return (y, x + 1, RIGHT)
    if d == DOWN and get(y + 1, x) == ".":
        return (y + 1, x, DOWN)
    if d == LEFT and get(y, x - 1) == ".":
        return (y, x - 1, LEFT)

    # else: rotate right
    return (y, x, (d + 1) % 4)


def outside(y, x, d):
    return (
        (d == UP and y == 0)
        or (d == RIGHT and x == XLEN - 1)
        or (d == DOWN and y == YLEN - 1)
        or (d == LEFT and x == 0)
    )


def part1(y, x):
    visits = set()
    visits.add((y, x))
    p = (y, x, UP)
    while not outside(*p):
        p = move(*p)
        visits.add((p[0], p[1]))
    print(len(visits))


def part2(ys, xs):
    res = 0

    def loopy(y, x):
        visits = set()
        p = (y, x, UP)
        while not outside(*p):
            if p in visits:
                return True
            visits.add(p)
            p = move(*p)
        return False

    for y in range(YLEN):
        for x in range(XLEN):
            if get(y, x) == ".":
                put(y, x, "#")
                loops = loopy(ys, xs)
                put(y, x, ".")
                if loops:
                    res += 1
    print(res)


s = start()
part1(*s)
part2(*s)
