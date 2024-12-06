#!/bin/env python


L = [l.strip() for l in open("input").readlines()]

UP = 0
RIGHT = 1
DOWN = 2
LEFT = 3

YLEN = len(L)
XLEN = len(L[0])


def start():
    for y, row in enumerate(L):
        for x, col in enumerate(row):
            if col == "^":
                L[y] = "".join(map(lambda c: "." if c == "^" else c, L[y]))
                return (y, x, UP)


def get(y, x):
    if 0 <= y < YLEN and 0 <= x < XLEN:
        return L[y][x]
    return "#"


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


def part1():
    visits = set()
    y, x, d = start()
    visits.add((y, x))
    while not (
        (d == UP and y == 0)
        or (d == RIGHT and x == XLEN - 1)
        or (d == DOWN and y == YLEN - 1)
        or (d == LEFT and x == 0)
    ):
        y, x, d = move(y, x, d)
        visits.add((y, x))

    print(len(visits))


part1()
