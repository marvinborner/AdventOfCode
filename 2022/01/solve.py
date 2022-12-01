data = [[int(calory) for calory in block.split("\n") if calory != ''] for block in open("input").read().split("\n\n")]

# i don't know list comprehension

def part1():
    res = 0
    for block in data:
        s = sum(block)
        if s > res:
            res = s
    return res

def part2():
    top3 = [0,0,0]
    for block in data:
        s = sum(block)
        m = min(top3)
        if s > m:
            top3.remove(m)
            top3.append(s)
    return sum(top3)

print(f"Part 1: {part1()}")
print(f"Part 2: {part2()}")
