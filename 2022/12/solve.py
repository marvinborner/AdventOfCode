import collections
import math

data = [
    [ord(x) - ord("a") for x in list(dat.strip())]
    for dat in open("input").readlines()
    if dat != ""
]


# literally straight out of my lecture
def bfs(grid, start, target):
    steps = [[math.inf] * len(grid[0]) for row in range(len(grid))]
    steps[start[0]][start[1]] = 0
    Q = collections.deque([start])
    while Q:
        prev = Q.popleft()
        for dest in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            # WHY CAN'T PYTHON ADD TUPLES?!
            new = (prev[0] + dest[0], prev[1] + dest[1])
            if (
                0 <= new[0] < len(grid)
                and 0 <= new[1] < len(grid[0])
                and steps[new[0]][new[1]] == math.inf
                and grid[new[0]][new[1]] - grid[prev[0]][prev[1]] <= 1
            ):
                steps[new[0]][new[1]] = steps[prev[0]][prev[1]] + 1
                Q.append(new)
    return steps[target[0]][target[1]]


def solve():
    S = [x for x in data if -14 in x][0]
    E = [x for x in data if -28 in x][0]
    S = (data.index(S), S.index(-14))
    E = (data.index(E), E.index(-28))
    data[S[0]][S[1]] = 0
    data[E[0]][E[1]] = 25
    print(f"Part 1: {bfs(data, S, E)}")
    # inefficient solutions are quite effective
    print(
        f"Part 2: {min(sum([[bfs(data, (y, x), E) for x in range(len(data[y])) if data[y][x] == 0] for y in range(len(data))], []))}"
    )


solve()
