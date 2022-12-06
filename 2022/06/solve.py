data = [dat for dat in open("input").readlines() if dat != ''][0]

def part1():
    for i in range(4, len(data)):
        if len(data[i-4:i]) == len(set(data[i-4:i])):
            return i

def part2():
    for i in range(14, len(data)):
        if len(data[i-14:i]) == len(set(data[i-14:i])):
            return i

print(f"Part 1: {part1()}")
print(f"Part 2: {part2()}")
