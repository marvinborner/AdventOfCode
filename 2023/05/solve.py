# I also wrote a solution in Haskell but it was much uglier than this..
# (and didn't fully work)

L = open("input").read().strip().split("\n\n")

p1 = float("infinity")
p2 = float("infinity")

seeds = []
mp = []

for b in L:
    ls = b.split("\n")
    if ls[0].startswith("seeds:"):
        seeds = [int(n) for n in ls[0].split(" ")[1:]]
        continue

    mp.append([])
    for m in ls[1:]:
        mp[len(mp) - 1].append([int(n) for n in m.split(" ")])

# part 1
for seed in seeds:
    curr = seed
    for m in mp:
        for dest, source, inc in m:
            if source <= curr < source + inc:
                curr += dest - source
                break
    p1 = min(curr, p1)

# part 2
for i in range(0, len(seeds), 2):
    start, length = seeds[i], seeds[i + 1]
    seed = start
    off = length
    while seed <= start + length:
        curr = seed
        for m in mp:
            for dest, source, inc in m:
                if source <= curr < source + inc:
                    off = max(min(off, source + inc - curr), 1)
                    curr += dest - source
                    break
        p2 = min(curr, p2)
        seed += off
        off = length - seed + start


print(p1)
print(p2)
