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


def solve(games):
    part1 = 0
    part2 = 0
    for i, game in games:
        red = max(c[0] for c in game if c[1] == "red")
        green = max(c[0] for c in game if c[1] == "green")
        blue = max(c[0] for c in game if c[1] == "blue")
        part1 += 0 if red > 12 or green > 13 or blue > 14 else i
        part2 += red * green * blue
    print(part1, part2)


solve([parse(l) for l in L])
