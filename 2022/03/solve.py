data = [dat.strip() for dat in open("input").read().split("\n") if dat != '']

def part1():
    res = 0

    for line in data:
        comp1 = list(line[len(line)//2:])
        comp2 = list(line[:len(line)//2])
        inter = list(set(comp1).intersection(comp2))[0]
        if inter.islower():
            res += ord(inter) - ord('a') + 1
        elif inter.isupper():
            res += ord(inter) - ord('A') + 27

    return res

def part2():
    res = 0

    for i in range(0, len(data), 3):
        common = list(set(data[i]).intersection(data[i+1]).intersection(data[i+2]))[0]
        if common.islower():
            res += ord(common) - ord('a') + 1
        elif common.isupper():
            res += ord(common) - ord('A') + 27

    return res

print(f"Part 1: {part1()}")
print(f"Part 2: {part2()}")
