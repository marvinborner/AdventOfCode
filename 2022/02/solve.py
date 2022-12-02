data = [dat.split(" ") for dat in open("input").read().split("\n") if dat != '']

# X Y Z = Rock Paper Scissors
# A B C = Rock Paper Scissors

def part1():
    res = 0

    choice=[1,2,3]
    mat = [3,6,0]
    factors = [1, 0, 2]
    mat = [0,3,6]
    for line in data:
        res += choice[ord(line[1]) - ord("X")]
        factor = factors[ord(line[0]) - ord("A")]
        rot = mat[factor:] + mat[:factor]
        res += rot[ord(line[1]) - ord("X")]

    return res

# X Y Z = lose draw win
# 1 2 3 = Rock Paper Scissors
# A B C = Rock Paper Scissors

def part2():
    res = 0

    choice = [0,3,6]
    mat = [3,1,2]

    for line in data:
        res += choice[ord(line[1]) - ord("X")]
        factor = ord(line[0]) - ord("A")
        rot = mat[factor:] + mat[:factor]
        res += rot[ord(line[1]) - ord("X")]

    return res

print(f"Part 1: {part1()}")
print(f"Part 2: {part2()}")
