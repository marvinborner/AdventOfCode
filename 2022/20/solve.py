import numpy as np

data = [
    (i, int(dat))
    for i, dat in enumerate(open("input").readlines())
    if dat != ""
]
size = len(data)


def solve(arr, mult):
    for coord in arr[:] * mult:
        i = arr.index(coord)
        arr.pop(i)
        arr.insert((i + coord[1]) % (size - 1), coord)
    zero = [coord[1] for coord in arr].index(0)
    locs = [1000, 2000, 3000]
    return sum(arr[(zero + p) % size][1] for p in locs)


def part1():
    copied = data[:]  # don't overwrite because part2
    return solve(copied, 1)


def part2():
    applied = [(i, dat * 811589153) for i, dat in data]
    return solve(applied, 10)


print(f"Part 1: {part1()}")
print(f"Part 2: {part2()}")
