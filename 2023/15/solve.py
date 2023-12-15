L = open("input").read().strip().split(",")


def hash(s):
    current = 0
    for c in s:
        current += ord(c)
        current *= 17
        current %= 256
    return current


def solve1():
    res = 0
    for l in L:
        res += hash(l)
    print(res)


def solve2():
    res = 0

    boxes = dict()  # defaultdict would be cheating!!1!!!1!
    for l in L:
        if l[-1] == "-":
            label = l[:-1]
            box = hash(label)
            boxes[box] = [
                (lab, foc) for (lab, foc) in boxes.get(box, []) if lab != label
            ]
        elif l[-2] == "=":
            label = l[:-2]
            focal = int(l[-1])
            box = hash(label)
            labels = [lab for (lab, foc) in boxes.get(box, [])]
            if label in labels:
                boxes[box] = [
                    (lab, focal if label == lab else foc)
                    for (lab, foc) in boxes[box]
                ]
            else:
                if box not in boxes:
                    boxes[box] = []
                boxes[box].append((label, focal))

    for i, stacked in boxes.items():
        for j, box in enumerate(stacked):
            res += (i + 1) * (j + 1) * box[1]
    print(res)


solve1()
solve2()
