B = [l.splitlines() for l in open("input").read().strip().split("\n\n")]


def solve(ls, delta):
    for row in range(1, len(ls)):
        errors = 0
        for prev, next in zip(ls[:row][::-1], ls[row:]):
            for p, n in zip(prev, next):
                if p == n:
                    continue
                errors += 1
        if errors == delta:
            return row
    return 0


print(sum(solve([*zip(*ls)], 0) + solve(ls, 0) * 100 for ls in B))
print(sum(solve([*zip(*ls)], 1) + solve(ls, 1) * 100 for ls in B))
