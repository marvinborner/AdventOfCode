const { _, performance } = require("perf_hooks");
const fs = require("fs");
const data = fs.readFileSync("input", "utf8");

function part_one() {
    let res = 0;

    return res;
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
