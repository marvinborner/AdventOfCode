# my initial solution for part 2 used matplotlib.path.contains_point

L = [list(l.strip()) for l in open("input").readlines()]
M = dict(((i, j), s) for i in range(len(L)) for j, s in enumerate(L[i]))


def start():
    return [p for p, s in M.items() if s == "S"][0]


def neighbours(pos):
    ps = []

    # north
    if pos[0] > 0 and M[pos] in "|JLS" and M[(pos[0]-1,pos[1])] in "|F7":
        ps.append((pos[0]-1,pos[1]))

    # south
    if pos[0] + 1 < len(L) and M[pos] in "|F7S" and M[(pos[0]+1,pos[1])] in "|LJ":
        ps.append((pos[0]+1,pos[1]))

    # east
    if pos[1] + 1 < len(L[0]) and M[pos] in "-LFS" and M[(pos[0],pos[1]+1)] in "-7J":
        ps.append((pos[0],pos[1]+1))

    # west
    if pos[1] > 0 and M[pos] in "-J7S" and M[(pos[0],pos[1]-1)] in "-FL":
        ps.append((pos[0],pos[1]-1))

    return ps

# rosetta
def area(loop):
    x,y = zip(*loop)
    return abs(
        sum(i * j for i, j in zip(x, y[1:] + y[:1]))
        - sum(i * j for i, j in zip(x[1:] + x[:1], y))
    ) // 2

# DFS
def solve():
    p = start()

    s = [p]
    v = []
    ds = {p: 0}

    while s:
        p = s.pop()
        if p in v:
            continue
        v.append(p)
        for n in neighbours(p):
            ds[n] = ds[p] + 1
            s.append(n)

    # part 1
    print(max(ds.values()) // 2)

    # part 2, picks theorem
    print(area(v) - (len(v) // 2) + 1)

solve()
