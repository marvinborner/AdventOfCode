L = [l.strip() for l in open("input").readlines()]

path = L[0]
nodes = dict(
    (p := n.split(" = ")) and (p[0], p[1][1:-1].split(", ")) for n in L[2:]
)


def part1(start):
    steps = 0
    curr = start
    while True:
        d = path[steps % len(path)]
        curr = nodes[curr][0 if d == "L" else 1]
        steps += 1
        if curr[2] == "Z":
            return steps


def lcm(steps):
    bi_gcd = lambda m, n: m if not n else bi_gcd(n, m % n)
    res = steps[0]
    for s in steps[1:]:
        res = s * (res // bi_gcd(res, s))
    return res


def part2():
    steps = []
    curr = [k for k in nodes.keys() if k[2] == "A"]
    for s in curr:
        steps.append(part1(s))

    # modulo ring yay
    return lcm(steps)


print(part1("AAA"))
print(part2())
