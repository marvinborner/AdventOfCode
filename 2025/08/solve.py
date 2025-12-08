#!/usr/bin/env python3

from heapq import nlargest
from math import dist, prod
from itertools import combinations

L = [
    (circuit, [int(c) for c in l.strip().split(",")])
    for circuit, l in enumerate(open("input").readlines())
]


def part1():
    combos = sorted(combinations(L, 2), key=lambda c: dist(c[0][1], c[1][1]))
    circuits = {c: c for c, _ in L}

    def circuit(box):
        if circuits[box] == box:
            return box
        c = circuit(circuits[box])
        circuits[box] = c
        return c

    for _ in range(1000):
        box1, box2 = combos.pop(0)
        circuit1, circuit2 = circuit(box1[0]), circuit(box2[0])
        if circuit1 != circuit2:
            circuits[circuit1] = circuit2

    counts = {}
    for i, _ in L:
        c = circuit(i)
        if c not in counts:
            counts[c] = 0
        counts[c] += 1

    print(prod(nlargest(3, counts.values())))


def part2():
    res = 0

    combos = sorted(combinations(L, 2), key=lambda c: dist(c[0][1], c[1][1]))
    circuits = {c: c for c, _ in L}

    def circuit(box):
        if circuits[box] == box:
            return box
        c = circuit(circuits[box])
        circuits[box] = c
        return c

    while True:
        box1, box2 = combos.pop(0)
        circuit1, circuit2 = circuit(box1[0]), circuit(box2[0])
        if circuit1 != circuit2:
            circuits[circuit1] = circuit2
            res += 1
            if res == 999:
                print(L[box1[0]][1][0] * L[box2[0]][1][0])
                return


part1()
part2()
