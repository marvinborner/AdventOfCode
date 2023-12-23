L = [l.strip() for y, l in enumerate(open("input").readlines())]

G = {}
for y in range(1, len(L) - 1):
    for x in range(1, len(L[0]) - 1):
        if L[y][x] == "#":
            continue
        if L[y - 1][x] != "#":
            if (y - 1, x) not in G:
                G[(y - 1, x)] = set()
            if (y, x) not in G:
                G[(y, x)] = set()
            G[(y - 1, x)].add((y, x, 1))
            G[(y, x)].add((y - 1, x, 1))
        if L[y][x - 1] != "#":
            if (y, x - 1) not in G:
                G[(y, x - 1)] = set()
            if (y, x) not in G:
                G[(y, x)] = set()
            G[(y, x - 1)].add((y, x, 1))
            G[(y, x)].add((y, x - 1, 1))

# compress graph
done = False
while not done:
    done = True
    for (y, x), ns in G.items():
        if len(ns) != 2:
            continue
        n1, n2 = ns
        G[n1[:2]].add((n2[0], n2[1], n1[2] + n2[2]))
        G[n2[:2]].add((n1[0], n1[1], n1[2] + n2[2]))
        G[n1[:2]].remove((y, x, n1[2]))
        G[n2[:2]].remove((y, x, n2[2]))
        del G[(y, x)]

        done = False
        break


def dfs(y, x):
    end = list(G.keys())[-1]
    ps = []
    st = []
    st.append((y, x, 1, set(), 1))
    while st:
        y, x, l, v, p = st.pop()
        v.add((y, x))
        ns = G[(y, x)]
        for n in ns:
            if n[:2] in v:
                continue

            np = p + n[2]
            st.append((*n, set(v), np))

            if n[:2] == end[:2]:  # reached end
                ps.append(np)

    print(max(p for p in ps))


dfs(0, 1)
