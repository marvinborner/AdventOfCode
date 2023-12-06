L = [
    [int(race) for race in l.strip().split(" ") if race and race[0].isdigit()]
    for l in open("input").readlines()
]


res = 1
for i in range(len(L[0])):
    winning = 0
    time, best = L[0][i], L[1][i]
    for hold in range(1, time):
        dist = hold * (time - hold)
        if dist > best:
            winning += 1
    res *= winning
print(res)

# for part 2, just join the numbers in the input :)
