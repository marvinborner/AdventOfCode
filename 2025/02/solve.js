const fs = require("fs");
const ranges = fs.readFileSync("input", "utf8").trim().split(",");

function isInvalid(start, num) {
  const len = num.length;

  for (let i = start; i <= len / 2; i++) {
    if (len % i != 0) continue;
    const nparts = len / i;
    const partlen = len / nparts;

    const parts = new Set();
    for (let part = 0; part < nparts; part++)
      parts.add(num.slice(part * partlen, (part + 1) * partlen));

    if (parts.size == 1) return true;
  }
  return false;
}

let part1 = 0;
let part2 = 0;
for (let range of ranges) {
  const [start, end] = range.split("-");
  for (let i = +start; i <= +end; i++) {
    let num = `${i}`;
    if (isInvalid(num.length / 2, num)) part1 += i;
    if (isInvalid(1, num)) part2 += i;
  }
}

console.log(part1, part2);
