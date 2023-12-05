L = open("input").read().strip().split("\n\n")


def part1():
    seeds = []
    mp = []

    allI = []

    for b in L:
        ls = b.split("\n")
        if ls[0].startswith("seeds:"):
            seeds = [int(n) for n in ls[0].split(" ")[1:]]
            continue

        mp.append({})
        curr = mp[len(mp) - 1]
        for m in ls[1:]:
            ms = [int(n) for n in m.split(" ")]
            for off in range(ms[2]):
                # curr[ms[1] + off] = ms[0] + off
                curr[ms[0] + off] = ms[1] + off
            allI += list(range(ms[0], ms[0] + ms[2]))

    # for i in range(len(mp) - 1, -1, -1):
    mn = float("infinity")
    res = 0
    for loc in allI:
        curr = mp[-1].get(loc, loc)
        for i in range(len(mp) - 2, -1, -1):
            curr = mp[i].get(curr, curr)
        print(loc, curr)
        if curr in seeds and loc < mn:
            mn = curr
            res = loc
    print(res)


part1()
