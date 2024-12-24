#!/bin/env python3

L = open("input").read().strip().split("\n\n")

wires = dict(
    (l.split(": ")[0], int(l.split(": ")[1])) for l in L[0].split("\n")
)
conns = dict(
    (l.split(" -> ")[1], l.split(" -> ")[0].split(" "))
    for l in L[1].split("\n")
)

regs = set(wires.keys()) | set(conns.keys())
zregs = sorted(r for r in regs if r[0] == "z")[::-1]


def eval(a, op, b):
    match op:
        case "AND":
            return a & b
        case "OR":
            return a | b
        case "XOR":
            return a ^ b
        case _:
            print("AAAH")
            return 0


def solve1(reg):
    if reg in wires:
        return wires[reg]
    a, op, b = conns[reg]
    return eval(solve1(a), op, solve1(b))


part1 = "".join(str(solve1(reg)) for reg in zregs)
print(int(part1, 2))
