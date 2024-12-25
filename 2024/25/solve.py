#!/bin/env python3

D = [d.split("\n") for d in open("input").read().strip().split("\n\n")]


def isKey(d):
    return "." in d[0] and "#" in d[-1]


def isLock(d):
    return "#" in d[0] and "." in d[-1]


def trans(d):
    return ["".join(d[j][i] for j in range(len(d))) for i in range(len(d[0]))]


def linearize(d):
    return list(map(lambda c: c.strip(".").count("#") - 1, trans(d)))


keys = []
locks = []
for d in D:
    if isKey(d):
        keys.append(linearize(d))
    elif isLock(d):
        locks.append(linearize(d))


def fits(key, lock):
    return not any(k + l >= 6 for k, l in zip(key, lock))


print(sum(fits(key, lock) for lock in locks for key in keys))
