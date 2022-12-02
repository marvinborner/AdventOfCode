data = [[ord(x) - (ord("X") if i == 1 else ord("A")) for i,x in enumerate(dat.split(" "))] for dat in open("input").read().split("\n") if dat != '']

def solve(choice, mat, factors):
    res = 0

    for line in data:
        factor = factors[line[0]]
        rot = mat[factor:] + mat[:factor]
        res += choice[line[1]] + rot[line[1]]

    return res

def part1():
    return solve([1,2,3], [0,3,6], [1,0,2])

def part2():
    return solve([0,3,6], [3,1,2], [0,1,2])

print(f"Part 1: {part1()}")
print(f"Part 2: {part2()}")
