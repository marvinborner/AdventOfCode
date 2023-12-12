L = [
    (p := l.strip().split(" ")) and (p[0], [int(n) for n in p[1].split(",")])
    for l in open("input").readlines()
]


# look mum no recursion!! :OOO
def arrangements(pat, sol):
    arr = 0
    done = [0]
    sols = [sol]
    pats = [pat]

    current = (tuple(sol),pat)

    while pats or sols:
        p = pats.pop()
        s = sols.pop()
        d = done.pop()

        if not p:
            arr += 1 if not s and not d else 0
            continue

        for ch in "#." if p[0] == "?" else p[0]:
            if ch == '#':
                sols.append(s)
                pats.append(p[1:])
                done.append(d + 1)
            elif not d:
                sols.append(s)
                pats.append(p[1:])
                done.append(0)
            elif s and s[0] == d:
                sols.append(s[1:])
                pats.append(p[1:])
                done.append(0)

    return arr


def part1():
    res = 0
    for pat, sol in L:
        res += arrangements(f".{pat}.", sol)
    print(res)


def part2():
    res = 0
    for pat, sol in L:
        res += arrangements("?".join([pat] * 5) + ".", sol * 5)
    print(res)


part1()
# part2()
