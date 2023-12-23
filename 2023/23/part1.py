# adapted from day 16

L = {
    (y, x): c
    for y, l in enumerate(open("input").readlines())
    for x, c in enumerate(l.strip())
    if c != "#"
}


def oob(y, x, d):
    return (y, x) not in L


def next(y, x, d):
    if d == 0:
        return (y - 1, x, d)
    if d == 1:
        return (y, x + 1, d)
    if d == 2:
        return (y + 1, x, d)
    if d == 3:
        return (y, x - 1, d)


def neighbours(y, x, d):
    ch = L[(y, x)]

    if ch == "^":
        return [next(y, x, 0)]
    if ch == ">":
        return [next(y, x, 1)]
    if ch == "v":
        return [next(y, x, 2)]
    if ch == "<":
        return [next(y, x, 3)]

    return [next(y, x, k) for k in range(4) if abs(d - k) != 2]


def dfs(y, x, d):
    end = list(L.keys())[-1]
    longest = 0
    ps = []
    st = []
    st.append((y, x, d, set(), 1))
    while st:
        y, x, d, v, p = st.pop()
        v.add((y, x))
        ns = neighbours(y, x, d)
        for n in ns:
            if n[:2] not in v and not oob(*n):
                np = p + 1
                st.append((*n, set(v), np))

                if n[:2] == end:  # reached end
                    ps.append(np)

    return ps


ps = dfs(0, 1, 2)
mx = max(p for p in ps)
print(mx - 1)
