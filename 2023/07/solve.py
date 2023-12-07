L = [
    (a := l.strip().split(" ")) and (a[0], int(a[1]))
    for l in open("input").readlines()
]

PART = 2

ORDER = "23456789TJQKA" if PART == 1 else "J23456789TQKA"

TYPES = [
    [1, 1, 1, 1, 1],  # high card
    [1, 1, 1, 2],  # one pair
    [1, 2, 2],  # two pair
    [1, 1, 3],  # three of a kind
    [2, 3],  # full house
    [1, 4],  # four of a kind
    [5],  # five of a kind
]


def hand_key(hand):
    return list(map(lambda x: ORDER.index(x), hand))


def hand_eval(hand):
    counts = sorted([hand.count(c) for c in set(hand)])
    return TYPES.index(counts)


def hand_type(hand):
    if PART == 1:
        return hand_eval(hand)
    combs = set(hand.replace("J", c) for c in ORDER[1:] if "J" in hand)
    combs.add(hand)
    return max(hand_eval(comb) for comb in combs)


def solve():
    types = []
    for hand, bid in L:
        types.append((hand_type(hand), hand, bid))
    types.sort(key=lambda t: t[0])

    grouped = [[a for a in types if a[0] == t] for t in range(len(TYPES))]
    for group in grouped:
        group.sort(key=lambda a: hand_key(a[1]))
    flat = [e for s in grouped for e in s]

    res = 0
    for rank in range(len(flat)):
        res += (rank + 1) * flat[rank][2]
    print(res)


solve()
