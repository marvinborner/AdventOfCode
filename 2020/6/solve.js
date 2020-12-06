const fs = require("fs");
const data = fs.readFileSync("input", "utf8");

function part_one()
{
    return data.split("\n\n").map(e => [...new Set(e.replace(/\n/g, ''))].join('').length).reduce((a, b) => a + b);
}

function part_two()
{
    let res = 0;

    data.split("\n\n").forEach(elem => {
        const line = elem.replace(/\n/g, '');
        const chars = line.split('');
        const cnt = elem.split('\n').length;
        for (const c of new Set(line))
            if (chars.filter(x => x == c).length == cnt)
                res++;
    });

    return res;
}

console.log(part_one());
console.log(part_two());
