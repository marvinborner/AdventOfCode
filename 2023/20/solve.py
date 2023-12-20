L = [
    (m := l.strip().split(" -> ")) and (m[0][1:], (m[0][0], m[1].split(", ")))
    for l in open("input").readlines()
]
L = dict(L)

state = {}

# init conjunctions to low pulse
for s, (_, ds) in L.items():
    for d in ds:
        k = ("&", d)
        if k not in state:
            state[k] = {}
        state[k][s] = False

rx = {k: 0 for k in state[("&", list(state[("&", "rx")].keys())[0])]}

for i in range(1, 424242):
    q = [("seeelefant", "roadcaster", False)]

    while q:
        s, m, p = q.pop(0)
        state[p] = state.get(p, 0) + 1

        if m not in L:
            continue

        k, ds = L[m]
        if k == "%":
            if p:
                continue
            else:
                state[(k, m)] = not state.get((k, m), False)
                p = state[(k, m)]
        elif k == "&":
            state[(k, m)][s] = p
            p = any(not x for x in state[(k, m)].values())

            if s in rx.keys():
                for _k in state[(k, m)].keys():
                    if state[(k, m)][_k]:
                        rx[_k] = i

        for d in ds:
            q.append((m, d, p))

    if i == 1000:  # part 1
        print(state[True] * state[False])
    if all(rx.values()):  # part 2
        print(eval("*".join(str(n) for n in rx.values())))
        break
