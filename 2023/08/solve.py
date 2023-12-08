L = [l.strip() for l in open("input").readlines()]

path = L[0]
nodes = dict(
    (p := n.split(" = ")) and (p[0], p[1][1:-1].split(", ")) for n in L[2:]
)


def part1():
    steps = 0
    curr = "AAA"
    while True:
        d = path[steps % len(path)]
        curr = nodes[curr][0 if d == "L" else 1]
        steps += 1
        if curr == "ZZZ":
            return steps


def part2():
    steps = 0
    curr = [k for k in nodes.keys() if k[2] == "A"]
    para = len(curr)
    while True:
        d = path[steps % len(path)]
        for i in range(para):
            curr[i] = nodes[curr[i]][0 if d == "L" else 1]
        steps += 1
        if len([k for k in curr if k[2] == "Z"]) == para:
            return steps


# print(part1())
print(part2())
