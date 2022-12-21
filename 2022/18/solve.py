import numpy as np

cubes = set(
    [
        tuple(int(c) for c in dat.split(","))
        for dat in open("input").readlines()
        if dat != ""
    ]
)


def sides(cube):
    i = np.identity(3, dtype=int)
    return set([tuple(cube + m) for m in np.vstack([i, -i])])


def part1():
    return sum(len(sides(cube) - cubes) for cube in cubes)


def part2():
    visited = set()
    q = [(0, 0, 0)]
    high = max(max(np.array(cubes).max(axis=0))) + 1
    while q:
        current = q.pop()
        sub = sides(current) - cubes - visited
        q += [side for side in sub if all(-1 <= val <= high for val in side)]
        visited.add(current)
    return sum((side in visited) for cube in cubes for side in sides(cube))


print(f"Part 1: {part1()}")
print(f"Part 2: {part2()}")
