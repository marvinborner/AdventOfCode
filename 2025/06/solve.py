from functools import reduce


def trans(M):
    return [[M[j][i] for j in range(len(M))] for i in range(len(M[0]))]


inp = open("input").readlines()
L1 = trans([[x for x in l.split()] for l in inp])


def part1():
    res = 0
    for l in L1:
        current = []
        for num in l[:-1]:
            current.append(int(num))

        if l[-1] == "*":
            lam = lambda x, y: x * y
        elif l[-1] == "+":
            lam = lambda x, y: x + y
        res += reduce(lam, current)
    print(res)


def part2():
    # stupid parsing
    indices = [
        *map(
            lambda t: t[0],
            filter(lambda f: f[1] != " ", enumerate(inp[-1])),
        )
    ]
    indices[-1] = len(inp[-1])
    L2 = []
    for l in inp:
        cur = []
        for i in range(len(indices) - 1):
            cur.append(l[indices[i] : indices[i + 1] - 1])
        L2.append(cur)
    L2 = trans(L2)

    res = 0
    for l in L2:
        nums = []
        for i in range(1, 6):  # only supports 6 digits..
            current = ""
            for num in l[:-1]:
                if i > len(num):
                    continue
                current += num[len(num) - i]

            if len(current) > 0:
                nums.append(int(current))

        if l[-1][0] == "*":
            lam = lambda x, y: x * y
        elif l[-1][0] == "+":
            lam = lambda x, y: x + y
        res += reduce(lam, nums)
    print(res)


part1()
part2()
