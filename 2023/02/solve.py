L = [l.strip() for l in open("input").readlines()]


def parse(l):
    game, cube_sets = l.split(": ")
    game = int(game.split(" ")[-1])
    cube_sets = [
        (l := cube.split(" "), (int(l[0]), l[1]))[1]
        for cubes in cube_sets.split("; ")
        for cube in cubes.split(", ")
    ]
    return game, cube_sets


def part1(games):
    res = 0
    for game in games:
        valid = True
        for cubes in game[1]:
            if (
                (cubes[0] > 12 and cubes[1] == "red")
                or (cubes[0] > 13 and cubes[1] == "green")
                or (cubes[0] > 14 and cubes[1] == "blue")
            ):
                valid = False
        if valid:
            res += game[0]
    print(res)


def part2(games):
    res = 0
    for game in games:
        red = max(c[0] for c in game[1] if c[1] == "red")
        green = max(c[0] for c in game[1] if c[1] == "green")
        blue = max(c[0] for c in game[1] if c[1] == "blue")
        res += red * green * blue
    print(res)


part1([parse(l) for l in L])
part2([parse(l) for l in L])
