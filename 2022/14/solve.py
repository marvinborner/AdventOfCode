data = [
    [[int(d) for d in r.split(",")] for r in dat.split(" -> ")]
    for dat in open("input").readlines()
    if dat != ""
]

X = 1000
Y = 500
SOURCE = [500, 0]

AIR = 0
ROCK = 1
SAND = 2
RESTED = 3


def rocks(grid, line):
    for i, (x, y) in enumerate(line[1:]):
        px = line[i][0]
        py = line[i][1]
        xmax, xmin = max(x, px), min(x, px)
        ymax, ymin = max(y, py), min(y, py)

        for lx in range(xmin, xmax + 1):
            for ly in range(ymin, ymax + 1):
                grid[lx][ly] = ROCK


def simulate(grid):
    falling = True
    while falling:
        # new sand drop!
        sand = SOURCE.copy()
        while True:
            if sand[1] >= Y - 1:
                falling = False
                break
            elif grid[sand[0]][sand[1] + 1] == AIR:
                sand[1] += 1
            elif grid[sand[0] - 1][sand[1] + 1] == AIR:
                sand[0] -= 1
                sand[1] += 1
            elif grid[sand[0] + 1][sand[1] + 1] == AIR:
                sand[0] += 1
                sand[1] += 1
            else:
                grid[sand[0]][sand[1]] = RESTED
                if sand == SOURCE:
                    falling = False
                break


def solve(grounded):
    grid = [[AIR] * Y for i in range(X)]
    for line in data:
        rocks(grid, line)

    if grounded:
        ground = max(y for _, y in sum(data, []))
        for x in range(X):
            grid[x][ground + 2] = ROCK

    simulate(grid)
    return sum(col.count(RESTED) for col in grid)


print(f"Part 1: {solve(False)}")
print(f"Part 2: {solve(True)}")
