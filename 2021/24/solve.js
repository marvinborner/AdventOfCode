const { _, performance } = require("perf_hooks");
const fs = require("fs");
const data = fs.readFileSync("input", "utf8").split("inp").map(block => block.split("\n")).slice(1);

function part_one() {
    let res = 0;

    // console.log(data);
    const xs = data.map(block => +block[5].split(" ").slice(-1)[0]);
    const ys = data.map(block => +block[15].split(" ").slice(-1)[0]);
    const zs = data.map(block => +block[4].split(" ").slice(-1)[0]);
    console.log(xs,ys,zs);

    let w = 89999999999999;
    while (1) {
        const ws = Array.from(String(w), Number);

        let z = 0;
        for (let i = 0; i < 14; i++) {
            let x = 0, y = 0;
            x = z;
            x %= 26;
            z = Math.floor(z / zs[i]);
            x += xs[i];
            x = (x == ws[i]) ? 0 : 1;
            y = 25;
            y *= x;
            y += 1;
            z *= y;
            y = ws[i] + ys[i];
            y *= x;
            z += y;
        }
        if (z == 0) {
            console.log("Found", w, x, y, z);
            break;
        }
        if (w % 1000000 == 0)
            console.log(w, z);
        w--;
    }

    return w;
}

function part_two() {
    let res = 0;

    return res;
}

const tic = performance.now();
console.log(part_one());
console.log(part_two());
const toc = performance.now();
console.log("TIME: " + ((toc - tic) / 1000).toFixed(6) + " seconds");
