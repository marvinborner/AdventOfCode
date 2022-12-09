data = [dat.split(" ") for dat in open("input").readlines() if dat != '']

def solve(n):
    knots = [[0,0] for i in range(n)]
    tails = set()
    for line in data:
        direction = line[0]
        amount = int(line[1])

        for i in range(amount):
            head = knots[0]
            head[0 if direction == "U" or direction == "D" else 1] += 1 if direction == "R" or direction == "U" else -1

            for knot in range(len(knots)-1):
                head, tail = knots[knot], knots[knot + 1]
                xd, yd = head[0]-tail[0], head[1]-tail[1]

                if abs(yd) > 1:
                    tail[1] += 1 if yd > 0 else -1
                    if abs(xd) > 0:
                        tail[0] += 1 if xd > 0 else -1
                elif abs(xd) > 1:
                    tail[0] += 1 if xd > 0 else -1
                    if abs(yd) > 0:
                        tail[1] += 1 if yd > 0 else -1

            tails.add(tuple(tail))

    return len(tails)

print(f"Part 1: {solve(2)}")
print(f"Part 2: {solve(10)}")
