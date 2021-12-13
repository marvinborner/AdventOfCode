const { _, performance } = require("perf_hooks");
const fs = require("fs");

const [dot_data, fold_data] = fs.readFileSync("input", "utf8").split("\n\n");

// Why doesn't JS have Tuples?!
class Tupility extends Set {
    add = (elem) =>
        super.add(typeof elem === "object" ? JSON.stringify(elem) : elem);
    iterable = () => [...this].map(JSON.parse);
}

function solve() {
    let dots = new Tupility();
    dot_data.split("\n").forEach((line) => {
        const [x, y] = line.split(",").map(Number);
        dots.add([x, y]);
    });

    let first = 0;
    fold_data.split("\n").forEach((line) => {
        let [dir, amount] = line.substr(11).split("=");
        if (!dir) return;
        amount = +amount;
        const changed = new Tupility();
        dots.iterable().forEach(([x, y]) =>
            changed.add([
                dir == "x" && x >= amount ? 2 * amount - x : x,
                dir == "y" && y >= amount ? 2 * amount - y : y,
            ])
        );
        dots = changed;
        if (!first) first = dots.size;
    });

    // ANSI escape sequences
    let out = process.stdout;
    out.write("\u001b[2J");
    dots.iterable().forEach(([x, y]) =>
        out.write("\u001b[" + (y + 1) + ";" + x + "H█")
    );

    console.log("\n\n" + first);
}

const tic = performance.now();
solve();
const toc = performance.now();
console.log("TIME: " + ((toc - tic) / 1000).toFixed(6) + " seconds");
