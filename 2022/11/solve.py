data = [
    [line.strip() for line in dat.split("\n")]
    for dat in open("input").read().split("\n\n")
    if dat != ""
]


def solve(part):
    monkeys = [
        {
            "items": [],
            "op": None,
            "divisibility": 1,
            "true": 0,
            "false": 0,
            "inspected": 0,
        }
        for i in range(len(data))
    ]

    # setup monkeys
    for i, block in enumerate(data):
        monkeys[i]["items"] = [
            int(item) for item in block[1].split(": ")[1].split(", ")
        ]
        monkeys[i]["op"] = block[2].split(": ")[1].replace("new = ", "")
        monkeys[i]["divisibility"] = int(block[3].split(" ")[-1])
        monkeys[i]["true"] = int(block[4].split(" ")[-1])
        monkeys[i]["false"] = int(block[5].split(" ")[-1])

    if part == 2:
        # evil muhahahaa
        common = eval(
            "*".join(str(monkey["divisibility"]) for monkey in monkeys)
        )

    for r in range(20 if part == 1 else 10000):
        current = 0
        while True:  # new round
            if current >= len(monkeys):
                break

            if len(monkeys[current]["items"]) == 0:
                current += 1
                continue

            monkeys[current]["inspected"] += 1
            old = monkeys[current]["items"].pop(0)
            lvl = eval(monkeys[current]["op"])
            lvl = int(lvl / 3) if part == 1 else lvl % common
            if lvl % monkeys[current]["divisibility"] == 0:
                monkeys[monkeys[current]["true"]]["items"].append(lvl)
            else:
                monkeys[monkeys[current]["false"]]["items"].append(lvl)

    bizz = sorted([monkey["inspected"] for monkey in monkeys])
    return bizz[-1] * bizz[-2]


print(f"Part 1: {solve(1)}")
print(f"Part 2: {solve(2)}")
