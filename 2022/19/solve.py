import re
from math import prod
import functools

all_costs = [
    [(s[1], 0, 0, 0), (s[2], 0, 0, 0), (s[3], s[4], 0, 0), (s[5], 0, s[6], 0)]
    for s in [
        [int(x) for x in re.findall(r"\d+", dat)]
        for dat in open("input").readlines()
        if dat != ""
    ]
]


def weight(state):  # from reddit, better than previously..
    mined = state[-1][-1]
    return 1000 * mined[3] + 100 * mined[2] + 10 * mined[1] + mined[0]


@functools.lru_cache
def bfs(current, bots, time_left, top):
    costs = all_costs[current]
    q = [(0, (bots, (0, 0, 0, 0), (0, 0, 0, 0)))]
    res = 0
    depth = 0
    while q:
        time, (bots, has, mined) = q.pop(0)

        if time == time_left:
            res = max(res, mined[3])
            continue

        if time > depth:
            q.sort(key=weight, reverse=True)
            q = q[:top]
            depth = time

        new_has = tuple(has[i] + bots[i] for i in range(4))
        new_mined = tuple(mined[i] + bots[i] for i in range(4))

        q.append((time + 1, (bots, new_has, new_mined)))

        for i in range(4):
            if any([has[j] < costs[i][j] for j in range(4)]):
                continue

            new_bots = bots[:i] + (bots[i] + 1,) + bots[(i + 1) :]
            new_has_state = tuple(new_has[j] - costs[i][j] for j in range(4))
            q.append((time + 1, (new_bots, new_has_state, new_mined)))
    return res


def part1():
    return sum(
        [
            bfs(i, (1, 0, 0, 0), 24, 1000) * (i + 1)
            for i in range(len(all_costs))
        ]
    )


def part2():
    return prod(
        [bfs(i, (1, 0, 0, 0), 32, 10000) for i in range(len(all_costs[:3]))]
    )


print(f"Part 1: {part1()}")
print(f"Part 2: {part2()}")
