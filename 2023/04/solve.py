L = [" ".join(l.split()) for l in open("input").readlines()]


def solve():
    p1 = 0
    p2 = [1] * len(L)
    for i, l in enumerate(L):
        card, nums = l.split(": ")
        winning, have = [
            list(map(int, a.split(" "))) for a in nums.split(" | ")
        ]
        s = sum(1 for x in have if x in winning)
        for j in range(i + 1, i + s + 1):
            p2[j] += p2[i]
        p1 += 0 if s == 0 else 2 ** (s - 1)
    print(p1, sum(p2))


solve()
