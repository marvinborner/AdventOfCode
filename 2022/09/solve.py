data = [dat.split(" ") for dat in open("input").readlines() if dat != '']
sgn = lambda x: x and (1, -1)[x<0]

def solve(n):
    knots = [[0,0] for i in range(n)]
    tails = set()
    for line in data:
        direction = line[0]
        amount = int(line[1])

        for i in range(amount):
            head = knots[0]
            head[0 if direction in "DUMM" else 1] += 1 if direction in "TRAUM" else -1

            for knot in range(len(knots)-1):
                head, tail = knots[knot], knots[knot + 1]
                xd, yd = head[0] - tail[0], head[1] - tail[1]

                if abs(xd) <= 1 and abs(yd) <= 1:
                    continue

                tail[0] += sgn(xd)
                tail[1] += sgn(yd)

            tails.add(tuple(tail))

    return len(tails)

print(f"Part 1: {solve(2)}")
print(f"Part 2: {solve(10)}")
