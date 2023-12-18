L = [
    (s := l.split(" ")) and (s[0], int(s[1]), s[2][2:-2])
    for l in open("input").readlines()
]


# rosetta, shoelace, day 10
def area(loop):
    x, y = zip(*loop)
    return abs(sum(i * j for i, j in zip(x, y[1:] + y[:1])) - sum(i * j for i, j in zip(x[1:] + x[:1], y))) // 2


def part1():
    mv = {"R": (0, 1), "D": (1, 0), "L": (0, -1), "U": (-1, 0)}

    c = (0, 0)
    mp = [c]
    for d, n, _ in L:
        nc = mv[d]
        c = (c[0] + nc[0] * n, c[1] + nc[1] * n)
        mp.append(c)

    s = sum(l[1] for l in L)
    print(area(mp) + s // 2 + 1)


def part2():
    mv = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    c = (0, 0)
    mp = [c]
    s = 0
    for _, _, h in L:
        n = int(h[:-1], 16)
        nc = mv[int(h[-1])]
        c = (c[0] + nc[0] * n, c[1] + nc[1] * n)
        s += n
        mp.append(c)

    print(area(mp) + s // 2 + 1)


part1()
part2()
