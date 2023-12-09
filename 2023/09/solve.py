L = [[int(n) for n in l.strip().split(" ")] for l in open("input").readlines()]


def predict(s):
    f = []
    while s:
        f.append(s[-1])
        s = [s[i] - s[i - 1] for i in range(1, len(s))]
    return sum(f)


print(sum(predict(l) for l in L))
print(sum(predict(l[::-1]) for l in L))
