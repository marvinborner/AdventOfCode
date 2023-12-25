L = {
    (s := l.strip().split(": ")) and s[0]: [-1, -1, False, set(s[1].split(" "))]
    for l in open("input").readlines()
}

# bidirectionality
for l in list(L.keys()):
    for k in L[l][3]:
        if k not in L:
            L[k] = [-1, -1, False, set()]
        L[k][3].add(l)


import networkx as nx  #  :)

cut = nx.minimum_edge_cut(
    nx.from_dict_of_lists({i: n[3] for (i, n) in L.items()})
)
for s, d in cut:
    L[s][3].remove(d)
    L[d][3].remove(s)


i = 0
s = []
res = 1


# probably overkill lol
def scc(n):
    # globalism ftw
    global i
    global s
    global res

    L[n] = [i, i, True, L[n][3]]
    i += 1
    s.append(n)

    for e in L[n][3]:
        if L[e][0] == -1:
            scc(e)
            L[n][1] = min(L[n][1], L[e][1])
        elif L[e][2]:
            L[n][1] = min(L[n][1], L[e][0])

    if L[n][1] == L[n][0]:
        comp = set()
        while True:
            e = s.pop()
            L[e][2] = False
            comp.add(e)
            if n == e:
                break
        res *= len(comp)


for n in L.keys():
    if L[n][0] == -1:
        scc(n)

print(res)
