data = [block.split("\n") for block in open("input").read().split("\n\n")]

# i don't know list comprehension

def part1():
    res = 0
    for block in data:
        sum = 0
        for calory in block:
            if len(calory) > 0:
                sum += int(calory)
        if sum > res:
            res = sum
    return res

def part2():
    top3 = [0,0,0]
    for block in data:
        s = 0
        for calory in block:
            if len(calory) > 0:
                s += int(calory)
        if s > min(top3):
            top3.remove(min(top3))
            top3.append(s)
    return sum(top3)

print(f"Part 1: {part1()}")
print(f"Part 2: {part2()}")
