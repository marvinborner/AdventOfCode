import sys

sys.setrecursionlimit(100000)

L = {
    (y, x): c
    for y, l in enumerate(open("input").readlines())
    for x, c in enumerate(l.strip())
    if c != "#"
}


def oob(y, x, d):
    return (y, x) not in L


def next(y, x, d):
    if d == 0:
        return (y - 1, x, d)
    if d == 1:
        return (y, x + 1, d)
    if d == 2:
        return (y + 1, x, d)
    if d == 3:
        return (y, x - 1, d)


def neighbours(y, x, d):
    ch = L[(y, x)]

    if ch == "^":
        return [next(y, x, 0)]
    if ch == ">":
        return [next(y, x, 1)]
    if ch == "v":
        return [next(y, x, 2)]
    if ch == "<":
        return [next(y, x, 3)]

    return [next(y, x, 0), next(y, x, 1), next(y, x, 2), next(y, x, 3)]


def dfs(y, x, d, v, p):
    v.add((y, x))

    ps = []
    ns = neighbours(y, x, d)
    for n in ns:
        if (n[0], n[1]) not in v and not oob(*n):
            np = p + [n]
            ps.append(tuple(np))
            ps.extend(dfs(*n, set(v), np))

    return ps


def solve1():
    ps = dfs(0, 1, 2, set(), [(0, 1)])
    mx = max(len(p) for p in ps)
    print(mx - 1)


# def solve2():
#     res = 0
#     for x in range(W):
#         res = max(res, visited(0, x, 2), visited(H, x, 0))
#     for y in range(H):
#         res = max(res, visited(y, 0, 1), visited(y, W, 3))
#     print(res)


solve1()
# solve2()
