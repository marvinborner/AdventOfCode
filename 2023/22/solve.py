L = [
    (a := l.strip().split("~"))
    and (b := [[int(x) for x in y.split(",")] for y in a])
    and [range(c[0], c[1] + 1) for c in (zip(*b))]
    for l in open("input").readlines()
]

L = sorted(L, key=lambda c: list(c)[2].start)


def gravity(L, ignore):
    res = 0
    mx = {}
    for i, (xs, ys, zs) in enumerate(L):
        if i == ignore:
            continue
        m = 0
        for x in xs:
            for y in ys:
                if mx.get((x, y), 0) > m:
                    m = mx.get((x, y))
        for x in xs:
            for y in ys:
                mx[(x, y)] = m - zs.start + zs.stop
        L[i] = (xs, ys, range(m, m - zs.start + zs.stop))
        if m < zs.start:
            res += 1
    return res


gravity(L, -1)

part1 = 0
part2 = 0
for i in range(len(L)):
    c = gravity(L.copy(), i)
    if c == 0:
        part1 += 1
    part2 += c

print(part1, part2)
