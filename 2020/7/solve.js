const fs = require("fs");
const data = fs.readFileSync("input", "utf8").split('\n');

function getMap()
{
    return data.reduce((map, line) => {
        const [superBag, subBags] = line.split(" contain ");
        const bag = superBag.split(" ").slice(0, -1).join(" ");
        if (!subBags || subBags == "no other bags.") {
            map[bag] = {};
        } else {
            map[bag] = subBags.split(", ").reduce((subMap, bags) => {
                const subBag = bags.split(" ");
                const subBagName = subBag.slice(1, -1).join(" ");
                subMap[subBagName] = +subBag[0];
                return subMap;
            }, {});
        }
        return map;
    }, {});
}

function inBag(map, superBag, subBag)
{
    if (map[superBag][subBag])
        return true;

    return Object.keys(map[superBag]).reduce((acc, key) => acc || inBag(map, key, subBag), false);
}

function countBags(map, bag)
{
    return Object.keys(map[bag]).reduce((acc, key) => acc + map[bag][key] * (1 + countBags(map, key)), 0);
}

function partOne()
{
    const map = getMap();
    return Object.keys(map).reduce((n, key) => n + inBag(map, key, "shiny gold"), 0);
}

function partTwo()
{
    const map = getMap();
    return countBags(map, "shiny gold");
}

console.log(partOne());
console.log(partTwo());
