data = [dat.strip().split(" ") for dat in open("input").readlines() if dat != '']

def solve():
    signal_strength = 0

    crt = [["?" for j in range(40)] for i in range(6)]
    col = row = 0

    x = 1
    cycle = timeout = i = 0
    while i < len(data):
        instr = data[i]

        if cycle > 0 and cycle % 40 == 0:
            col = 0
            row += 1

        cycle += 1

        if cycle - 20 >= 0 and (cycle - 20) % 40 == 0:
            signal_strength += cycle * x

        crt[row][col] = "█" if col in [x-1,x,x+1] else " "
        col += 1

        if instr[0] == "noop":
            i += 1
        elif timeout > 0 and instr[0] == "addx":
            timeout -= 1
            if timeout == 0:
                x += int(instr[1])
                i += 1
        elif timeout == 0 and instr[0] == "addx":
            timeout = 1

    print(f"Part 1: {signal_strength}")
    print("\n".join(["".join(row) for row in crt]))

solve()
