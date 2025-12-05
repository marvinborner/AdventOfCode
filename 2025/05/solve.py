#!/bin/env python

fresh, ingredients = open("input").read().split("\n\n")
fresh = sorted(
    [tuple(int(id) for id in f.split("-")) for f in fresh.strip().split("\n")]
)
ingredients = [int(id) for id in ingredients.strip().split("\n")]


def part1():
    res = 0
    for ingredient in ingredients:
        for start, end in fresh:
            if ingredient in range(start, end + 1):
                res += 1
                break
    print(res)


def part2():
    res = 0
    prev = 0
    for start, end in fresh:
        if prev >= start:
            start = prev + 1
        if end > prev:
            prev = end
        res += len(range(start, end + 1))
    print(res)


part1()
part2()
