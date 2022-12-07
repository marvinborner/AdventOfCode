data = [dat.strip() for dat in open("input").readlines() if dat != '']

def sum_dir(d):
    s = 0
    for file in d:
        s += int(file[1])
    return s

def solve():
    fs = {"/": []}
    path = []

    i = 0
    while i < len(data):
        line = data[i]
        i += 1
        if line[0] == "$":
            if line[2] == "c":
                if line[5:] == "..":
                    del path[-1]
                else:
                    path.append(line[5:])
            if line[2] == "l":
                top = fs["/".join(path)]
                if not top:
                    top = []
                while i < len(data) and data[i][0] != "$":
                    if data[i][0] == "d":
                        fs["/".join(path)+"/"+data[i][4:]] = []
                    else:
                        s,n = data[i].split(" ")
                        fs["/".join(path)].append((n, s))
                    i += 1

    aah = []
    for elem in fs:
        s = sum_dir(fs[elem])
        for sub in fs:
            if sub != elem and sub.startswith(elem):
                s += sum_dir(fs[sub])
        aah.append(s)

    used = aah[0]
    total = 70000000-used
    to_free = 30000000-total

    to_delete = []
    for elem in aah:
        if elem > to_free:
            to_delete.append(elem)

    return min(to_delete)

print(solve())
