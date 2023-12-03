L = [list(l.strip()) for l in open("input").readlines()]


def part1():
    res = 0
    for i, l in enumerate(L):
        current = ""
        has_adjacent = False

        for j, m in enumerate(l + ["."]):
            if not m.isdigit():
                if has_adjacent:
                    res += int(current)
                current = ""
                has_adjacent = False
                continue

            current += m

            # next line
            if i + 1 < len(L) and any(
                x != "." for x in L[i + 1][j - 1 : j + 2]
            ):
                has_adjacent = True

            # previous line
            if i - 1 >= 0 and any(x != "." for x in L[i - 1][j - 1 : j + 2]):
                has_adjacent = True

            # left + right char
            left = l[j - 1] if j - 1 >= 0 else "."
            right = l[j + 1] if j + 1 < len(l) else "."
            if (not left.isdigit() and left != ".") or (
                not right.isdigit() and right != "."
            ):
                has_adjacent = True
    print(res)


def part2():
    gears = {}

    for i, l in enumerate(L):
        current = ""
        has_adjacent = False

        for j, m in enumerate(l + ["."]):
            if not m.isdigit():
                if has_adjacent:
                    if gear not in gears:
                        gears[gear] = []
                    gears[gear].append(int(current))
                current = ""
                has_adjacent = False
                continue

            current += m

            # next line
            next = L[i + 1][j - 1 : j + 2] if i + 1 < len(L) else []
            if any(x == "*" for x in next):
                gear = (i + 1, j - 1 + next.index("*"))
                has_adjacent = True

            # previous line
            prev = L[i - 1][j - 1 : j + 2] if i - 1 >= 0 else []
            if any(x == "*" for x in prev):
                gear = (i - 1, j - 1 + prev.index("*"))
                has_adjacent = True

            # left char
            left = l[j - 1] if j - 1 >= 0 else "."
            if left == "*":
                gear = (i, j - 1)
                has_adjacent = True

            # right char
            right = l[j + 1] if j + 1 < len(l) else "."
            if right == "*":
                gear = (i, j + 1)
                has_adjacent = True

    print(sum(gear[0] * gear[1] for gear in gears.values() if len(gear) == 2))


part1()
part2()
