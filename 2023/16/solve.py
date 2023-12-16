L = {
    (y, x): c
    for y, l in enumerate(open("input").readlines())
    for x, c in enumerate(l.strip())
}

W = max(x for (_, x) in L.keys())
H = max(y for (y, _) in L.keys())


def oob(y, x, d):
    return x > W or x < 0 or y > H or y < 0


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

    # rule 1
    if ch == ".":
        return [next(y, x, d)]

    # rule 2
    if ch == "/":
        r = [1, 0, 3, 2]
        return [next(y, x, r[d])]
    if ch == "\\":
        r = [3, 2, 1, 0]
        return [next(y, x, r[d])]

    # rule 3
    if ch == "|" and d in [1, 3]:
        return [(y - 1, x, 0), (y + 1, x, 2)]
    if ch == "-" and d in [0, 2]:
        return [(y, x + 1, 1), (y, x - 1, 3)]

    # rule 4
    if ch == "|" and d in [0, 2] or ch == "-" and d in [1, 3]:
        return [next(y, x, d)]


def visited(sy, sx, sd):
    q = [(sy, sx, sd)]
    v = set()
    v.add(q[0])

    while q:
        y, x, d = q.pop(0)

        ns = neighbours(y, x, d)
        for n in ns:
            if n not in v and not oob(*n):
                v.add(n)
                q.append(n)

    return len(set((y, x) for (y, x, _) in v))


def solve1():
    print(visited(0, 0, 1))


def solve2():
    res = 0
    for x in range(W):
        res = max(res, visited(0, x, 2), visited(H, x, 0))
    for y in range(H):
        res = max(res, visited(y, 0, 1), visited(y, W, 3))
    print(res)


solve1()
solve2()
