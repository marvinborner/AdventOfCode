data = [[[int(wtf) for wtf in uff.split("-")] for uff in dat.split(",")] for dat in open("input").readlines() if dat != '']

def part1():
    return len([42 for a,b in data if a[0] >= b[0] and a[1] <= b[1] or b[0] >= a[0] and b[1] <= a[1]])

def part2():
    return len([42 for a,b in data if a[0] <= b[1] and b[0] <= a[1]])

print(f"Part 1: {part1()}")
print(f"Part 2: {part2()}")
