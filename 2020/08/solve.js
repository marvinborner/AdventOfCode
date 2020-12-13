const { _, performance } = require("perf_hooks");
const fs = require("fs");
const data = fs.readFileSync("input", "utf8").split('\n');

function run(code)
{
    let acc = 0;
    let visited = [];

    let i = 0;
    while (!visited.includes(i)) {
        visited.push(i);
        if (!code[i])
            return { acc, i };

        const [op, cnt] = code[i].split(" ");;
        switch (op) {
            case "acc":
                acc += +cnt;
                break;
            case "jmp":
                i += +cnt - 1;
                break;
            default:
                break;
        }
        i++;
    }
    return { acc, i };
}

function partOne()
{
    return run(data).acc;
}

function partTwo()
{
    for (let i = 0; i < data.length; i++) {
        const [op, cnt] = data[i].split(" ");;
        if (op == "acc")
            continue; // Skip correction

        let fixed = [...data];
        fixed.splice(i, 1, `${op == "nop" ? "jmp" : "nop"} ${cnt}`);
        let results = run(fixed);
        if (results.i == fixed.length)
            return results.acc;
    }
}

const tic = performance.now();
console.log(partOne());
console.log(partTwo());
const toc = performance.now();
console.log("TIME: " + ((toc - tic) / 1000).toFixed(6) + " seconds");
