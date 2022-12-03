data = [dat.strip() for dat in open("input").read().split("\n") if dat != '']

def calc(a):
    return ord(a) - (ord('a') - 1 if a.islower() else ord('A') - 27)

def part1():
    res = 0

    for line in data:
        h = len(line)//2
        comp1 = set(line[h:])
        comp2 = set(line[:h])
        inter = comp1.intersection(comp2).pop()
        res += calc(inter)

    return res

def part2():
    res = 0

    for i in range(0, len(data), 3):
        common = set(data[i]).intersection(data[i+1]).intersection(data[i+2]).pop()
        res += calc(common)

    return res

print(f"Part 1: {part1()}")
print(f"Part 2: {part2()}")
