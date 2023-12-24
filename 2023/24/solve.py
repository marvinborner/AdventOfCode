import numpy as np

L = [
    [[int(x) for x in b.strip().split(", ")] for b in l.split(" @ ")]
    for l in open("input").readlines()
]


def collision(x1, y1, vx1, vy1, x2, y2, vx2, vy2):
    a1 = np.array([x1, y1]).T
    v1 = np.array([vx1, vy1]).T
    a2 = np.array([x2, y2]).T
    v2 = np.array([vx2, vy2]).T
    sect, _, rank, *rst = np.linalg.lstsq(
        np.array([v1, v2]).T, a2 - a1, rcond=None
    )
    if rank == 2:
        return a1 + v1 * sect[0]
    return np.array([-1, -1])


res = 0
# MIN = 7
# MAX = 27
MIN = 200000000000000
MAX = 400000000000000
for i, ((x1, y1, z1), (vx1, vy1, vz1)) in enumerate(L):
    for j, ((x2, y2, z2), (vx2, vy2, vz2)) in enumerate(L[i + 1 :]):
        x, y = collision(x1, y1, vx1, vy1, x2, y2, vx2, vy2)
        res += (
            MIN <= x <= MAX
            and MIN <= y <= MAX
            and (x - x1) * vx1 >= 0
            and (y - y1) * vy1 >= 0
            and (x - x2) * vx2 >= 0
            and (y - y2) * vy2 >= 0
        )

print(res)
