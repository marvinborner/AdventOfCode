data = [list(dat.strip()) for dat in open("input").readlines() if dat != '']

def part1():
    res = 0
    for i in range(1,len(data)-1):
        for j in range(1,len(data[0])-1):
            sight = [True,True,True,True]

            for l in range(0, i):
                if data[l][j] >= data[i][j]:
                    sight[0] = False
            for l in range(0, j):
                if data[i][l] >= data[i][j]:
                    sight[1] = False
            for l in range(len(data[0])-1,j,-1):
                if data[i][l] >= data[i][j]:
                    sight[2] = False
            for l in range(len(data)-1,i,-1):
                if data[l][j] >= data[i][j]:
                    sight[3] = False
            if any(sight):
                res += 1

    return res + ((len(data)+len(data[0]))*2-4)

def part2():
    res = []
    for i in range(1,len(data)-1):
        for j in range(1,len(data[0])-1):
            sight = [0,0,0,0]

            for l in range(i-1, -1, -1):
                sight[0] += 1
                if data[l][j] >= data[i][j]:
                    break
            for l in range(j-1, -1, -1):
                sight[1] += 1
                if data[i][l] >= data[i][j]:
                    break
            for l in range(j+1, len(data[0])):
                sight[2] += 1
                if data[i][l] >= data[i][j]:
                    break
            for l in range(i+1, len(data)):
                sight[3] += 1
                if data[l][j] >= data[i][j]:
                    break
            res.append([x:=1,[x:=x*s for s in sight]][-1][-1]) # Woah!

    return max(res)

print(f"Part 1: {part1()}")
print(f"Part 2: {part2()}")
