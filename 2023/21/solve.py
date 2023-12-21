L = {
    (i, j): c
    for (i, l) in enumerate(open("input").readlines())
    for (j, c) in enumerate(l.strip())
}


def solve1():
    LIM = 64

    res = 0
    s = [(i, j) for (i, j) in L if L[(i, j)] == "S"][0]
    q = [(s, 0)]
    v = set()
    while q:
        p, n = q.pop(0)
        if n == LIM + 1:
            continue

        for move in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
            np = (p[0] + move[0], p[1] + move[1])
            if np not in L or np in v or L[np] == "#":
                continue
            q.append((np, n + 1))
            v.add(np)
            if n % 2:
                res += 1
    print(res)


solve1()
