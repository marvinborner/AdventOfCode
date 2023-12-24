import numpy as np
import z3

L = [
    [[int(x) for x in b.strip().split(", ")] for b in l.split(" @ ")]
    for l in open("input").readlines()
]


def collision2(x1, y1, vx1, vy1, x2, y2, vx2, vy2):
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


def part1():
    res = 0
    MIN = 200000000000000
    MAX = 400000000000000
    for i, ((x1, y1, z1), (vx1, vy1, vz1)) in enumerate(L):
        for j, ((x2, y2, z2), (vx2, vy2, vz2)) in enumerate(L[i + 1 :]):
            x, y = collision2(x1, y1, vx1, vy1, x2, y2, vx2, vy2)
            res += (
                MIN <= x <= MAX
                and MIN <= y <= MAX
                and (x - x1) * vx1 >= 0
                and (y - y1) * vy1 >= 0
                and (x - x2) * vx2 >= 0
                and (y - y2) * vy2 >= 0
            )

    print(res)


def part2():
    solver = z3.Solver()

    z3x = z3.FreshInt()
    z3y = z3.FreshInt()
    z3z = z3.FreshInt()
    z3vx = z3.FreshInt()
    z3vy = z3.FreshInt()
    z3vz = z3.FreshInt()

    for i, ((x, y, z), (vx, vy, vz)) in enumerate(L):
        s = z3.FreshInt()
        solver.add(s >= 0)
        solver.add(z3x + z3vx * s == x + vx * s)
        solver.add(z3y + z3vy * s == y + vy * s)
        solver.add(z3z + z3vz * s == z + vz * s)

    solver.check()
    model = solver.model()
    print(
        model.eval(z3x).as_long()
        + model.eval(z3y).as_long()
        + model.eval(z3z).as_long()
    )


part1()
part2()
