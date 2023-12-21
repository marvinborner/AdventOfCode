L = {
    (i, j): c
    for (i, l) in enumerate(open("input").readlines())
    for (j, c) in enumerate(l.strip())
}

W = max(j for (i, j) in L.keys()) + 1
C = W // 2


# from day 9
def predict(s):
    f = []
    while s:
        f.append(s[-1])
        s = [s[i] - s[i - 1] for i in range(1, len(s))]
    return sum(f)


# more efficient than predict
from numpy.polynomial import Polynomial


FIN = 26501365
PREHEAT = 5
LIM1 = 64
LIM2 = C + PREHEAT * W

pre = {-1: 0}
s = [(i, j) for (i, j) in L if L[(i, j)] == "S"][0]
q = [(s, 0)]
v = set()

part1 = 0

while q:
    p, n = q.pop(0)
    if n == LIM1 and not part1:
        part1 = pre[LIM1 - 1]
    if n == LIM2:
        break

    for move in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
        np = (p[0] + move[0], p[1] + move[1])
        _np = (np[0] % W, np[1] % W)
        if _np not in L or np in v or L[_np] == "#":
            continue
        q.append((np, n + 1))
        v.add(np)
        if n % 2:
            if n not in pre:
                pre[n] = pre[n - 2]
            pre[n] += 1

print(part1)
print(pre)

poly = {}
for i in range(PREHEAT):
    j = C + i * W
    if j % 2:
        poly[i] = pre[j]

print(poly)
f = Polynomial.fit(list(poly.keys()), list(poly.values()), 2)
x = (FIN - C) / W
res = f(x)
print(f, x, round(res))

# for i in range(PREHEAT, (FIN - C) / W + 1):
#     poly.append(predict(poly))
