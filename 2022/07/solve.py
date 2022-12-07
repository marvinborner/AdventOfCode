data = [dat.strip() for dat in open("input").readlines() if dat != '']

def solve():
    fs = {"/": []}
    path = []

    i = 0
    while i < len(data):
        line = data[i]
        i += 1
        if line[2] == "c":
            if line[5:] == "..":
                del path[-1]
            else:
                path.append(line[5:])
        if line[2] == "l":
            top = fs["/".join(path)]
            while i < len(data) and data[i][0] != "$":
                if data[i][0] == "d":
                    fs["/".join(path)+"/"+data[i][4:]] = []
                else:
                    s,_ = data[i].split(" ")
                    fs["/".join(path)].append(int(s))
                i += 1

    all_sizes = []
    part1 = 0
    for elem in fs:
        s = sum(fs[elem])
        s += sum(sum(fs[sub]) for sub in fs if sub != elem and sub.startswith(elem))
        if s < 100000:
            part1 += s
        all_sizes.append(s)

    print(f"Part 1: {part1}")

    to_free = 30000000-70000000+all_sizes[0]
    part2 = min(elem for elem in all_sizes if elem > to_free)
    print(f"Part 2: {part2}")

solve()
