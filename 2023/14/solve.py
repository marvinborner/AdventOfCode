L = [l.strip() for l in open("input").readlines()]


def tilt(mp, d):
    transposed = d == 0 or d == 2
    if transposed:  # north or south
        mp = list(map(list, zip(*mp)))

    pat = ".O" if d == 0 or d == 1 else "O."

    done = False
    while not done:
        done = True
        for l in mp:
            for i in range(len(l) - 1):
                if f"{l[i]}{l[i+1]}" != pat:
                    continue
                l[i + 1], l[i] = l[i], l[i + 1]
                done = False

    if transposed:  # north or south
        mp = list(map(list, zip(*mp)))

    return mp


def load(mp):
    res = 0
    for i, l in enumerate(mp):
        res += (len(mp) - i) * l.count("O")
    return res


def part1():
    res = 0
    mp = tilt(L, 0)
    print(load(mp))


def part2():
    res = 0

    hist = {}
    cycle = 0

    mp = L
    i = 0
    while True:
        mp = tilt(mp, 0)
        mp = tilt(mp, 1)
        mp = tilt(mp, 2)
        mp = tilt(mp, 3)

        if cycle:
            if i % cycle == 0:
                break
        else:
            key = tuple(tuple(l) for l in mp)
            if key in hist:
                cycle = i - hist[key] - 1
            else:
                hist[key] = i

        i += 1

    res = 0
    for j, l in enumerate(mp):
        res += (len(mp) - j) * l.count("O")
    print(res)


part1()
part2()
