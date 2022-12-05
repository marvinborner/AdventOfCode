data = [dat for dat in open("input").readlines() if dat != '']

def solve(mover_version):
    # lists >> stacks hehe
    stacks = [[] for i in range(len(data[0]) // 4)]

    start = True
    for line in data:
        if start:
            if line[0] == '\n':
                start = False
                continue

            cols = line.strip()
            i = 1
            while i < len(cols):
                if cols[i-1] == '[':
                    stacks[i // 4].insert(0, cols[i])
                i += 4
        else:
            proc = line.replace("move ", "").replace("from ", "").replace("to ", "").replace("target ", "").split(" ")
            what = int(proc[0])
            source = int(proc[1]) - 1
            target = int(proc[2]) - 1

            crates = stacks[source][-what:]
            if mover_version == 9000:
                crates = crates[::-1]
            stacks[target] += crates
            stacks[source] = stacks[source][:-what]

    print(f"Part {'1' if mover_version == 9000 else '2'}: {''.join([stack[-1] for stack in stacks if len(stack) > 0])}")

solve(9000)
solve(9001)
