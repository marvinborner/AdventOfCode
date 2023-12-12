L = [
    (p := l.strip().split(" ")) and (p[0], [int(n) for n in p[1].split(",")])
    for l in open("input").readlines()
]


def groups(pat):
    gs = []
    c = []
    for p in pat:
        if p in "#?":
            c.append(p)
        elif c:
            gs.append(c)
            c = []
    return gs[::-1]


def arrangements(pat, sol):
    arr = 1

    gs = groups(pat)
    for i, g in enumerate(gs):
        if len(g) == sol[0]:  # ???.[#??] 1,1,[3]
            del sol[0]
            continue
        if g.count("#") == 0:
            if len(g) == len(sol) + 1 and len(sol) == sum(sol):  # [???].### [1,1],3
                break
            # if len(g) > len(sol)
        print(g, sol)

    return arr


def part1():
    res = 0
    for pat, sol in L:
        res += arrangements(f".{pat}.", sol[::-1])
    print(res)


part1()
