NORTH=0
EAST=1
SOUTH=2
WEST=3

data=[dat.strip() for dat in open("input", "r").read().split(",")]

def part1():
    pos=[0,0]
    rotation=0

    for instruction in data:
        rotation+=1 if instruction[0] == 'R' else -1
        if rotation % 2 == 0:
            pos[1]+=int(instruction[1:])*(-1 if rotation % 4 == SOUTH else 1)
        else:
            pos[0]+=int(instruction[1:])*(-1 if rotation % 4 == WEST else 1)
    return pos[0]+pos[1]

print(part1())
