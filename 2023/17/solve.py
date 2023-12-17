from queue import PriorityQueue

L = {
    (y, x): int(c)
    for y, l in enumerate(open("input").readlines())
    for x, c in enumerate(l.strip())
}


W = max(x for (_, x) in L.keys())
H = max(y for (y, _) in L.keys())


def oob(y, x, d, c):
    return x > W or x < 0 or y > H or y < 0


def neighbours(y, x, d, c):
    ns = []
    if d != 2:
        ns.append((y - 1, x, 0, c + 1 if d == 0 else 0))
    if d != 3:
        ns.append((y, x + 1, 1, c + 1 if d == 1 else 0))
    if d != 0:
        ns.append((y + 1, x, 2, c + 1 if d == 2 else 0))
    if d != 1:
        ns.append((y, x - 1, 3, c + 1 if d == 3 else 0))
    return ns


def part1():
    q = PriorityQueue()
    q.put((0, (0, 0, 1, 0)))
    v = set()

    while q:
        p, c = q.get()

        if c[:2] == (H, W):
            break

        if c in v:
            continue
        v.add(c)

        for n in neighbours(*c):
            if not oob(*n) and c[3] < 3:
                q.put((p + L[n[:2]], n))

    print(p)


def part2():
    q = PriorityQueue()
    q.put((0, (0, 0, 1, 0)))
    v = set()

    while q:
        p, c = q.get()

        if c[:2] == (H, W) and c[3] >= 3:
            print(p)
            break

        if c in v:
            continue
        v.add(c)

        for n in neighbours(*c):
            if n[2] != c[2] and c[3] < 3:
                continue
            if not oob(*n) and n[3] < 10:
                q.put((p + L[n[:2]], n))


part1()
part2()
