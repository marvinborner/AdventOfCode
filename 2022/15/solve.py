import re
import os
import concurrent.futures

data = [
    [int(s) for s in re.findall(r"-?\d+", dat)]
    for dat in open("input").readlines()
    if dat != ""
]

dists = [
    abs(sensor_x - beacon_x) + abs(sensor_y - beacon_y)
    for sensor_x, sensor_y, beacon_x, beacon_y in data
]

P1 = 2000000
P2 = 4000000


def part1():
    noped = set()
    already = set()
    for i, (sensor_x, sensor_y, beacon_x, beacon_y) in enumerate(data):
        dist = dists[i] - abs(sensor_y - P1)
        if beacon_y == P1:
            already.add(beacon_x)
        if dist >= 0:
            noped.add(range(sensor_x - dist, sensor_x + dist + 1))
    return len(set.union(*[set(x) for x in noped]) - already)


def valid(x, y):
    for i, (sensor_x, sensor_y, _, _) in enumerate(data):
        dist = abs(sensor_x - x) + abs(sensor_y - y)
        if dist < dists[i]:
            return False
    return True


def aah(i):
    sensor_x, sensor_y, _, _ = data[i]
    for mult_x, mult_y in (-1, 1), (-1, 1):
        for dist_x in range(dists[i] + 2):
            x = sensor_x + dist_x * mult_x
            dist_y = dists[i] + 1 - dist_x
            y = sensor_y + dist_y * mult_y
            if x in range(0, P2 + 1) and y in range(0, P2 + 1) and valid(x, y):
                res = x * P2 + y
                return res
    return False


def part2():
    executor = concurrent.futures.ProcessPoolExecutor(10)
    futures = [executor.submit(aah, i) for i in range(len(data))]
    for f in concurrent.futures.as_completed(futures):
        res = f.result()
        if res:
            return res
    return 0


print(f"Part 1: {part1()}")
print(f"Part 2: {part2()}")
os.kill(os.getpid(), 9)  # nice way to kill workers
