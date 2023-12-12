L = [
    (p := l.strip().split(" ")) and (p[0], [int(n) for n in p[1].split(",")])
    for l in open("input").readlines()
]

# couldn't get caching to work without recursion
cache = {}


# see previous commit for no recursion
def arrangements(pat, sol, done):
    if (pat, sol, done) in cache:
        return cache[(pat, sol, done)]

    if not pat:
        return 1 if not sol and not done else 0

    arr = 0

    for ch in "#." if pat[0] == "?" else pat[0]:
        rst = pat[1:]
        if ch == "#":
            arr += arrangements(rst, sol, done + 1)
        elif not done:
            arr += arrangements(rst, sol, 0)
        elif sol and sol[0] == done:
            arr += arrangements(rst, sol[1:], 0)
        cache[(pat, sol, done)] = arr

    return arr


def part1():
    res = 0
    for pat, sol in L:
        res += arrangements(f".{pat}.", tuple(sol), 0)
    print(res)


def part2():
    res = 0
    for pat, sol in L:
        res += arrangements("?".join([pat] * 5) + ".", tuple(sol * 5), 0)
    print(res)


part1()
part2()
