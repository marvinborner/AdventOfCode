const { _, performance } = require("perf_hooks");
const fs = require("fs");
const data = fs
  .readFileSync("input", "utf8")
  .split("\n")[0]
  .split("")
  .map((x) => parseInt(x));

function partOne() {
  let moves = 11;

  let cur = 0;
  const cups = data;
  while (--moves) {
    // Pick up
    const picks = [];
    for (let i = 0; i < 3; i++) picks[i] = cups.splice(cur + 1, 1);

    // Find destination
    let dest = 0;
    let decr = 1;
    while (!dest) {
      dest = cups.filter((x) => x == cups[cur] - decr)[0];
      if (!dest) decr++;

      if (decr > cups.length) {
        dest = Math.max.apply(Math, cups);
        break;
      }
    }

    cups.splice.apply(cups, [cups.indexOf(dest) + 1, 0].concat(picks));
    console.log("Cups: " + cups, "Picks: " + picks, "Dest: " + dest);

    cur++;
  }
  return 0;
}

function partTwo() {
  return 0;
}

const tic = performance.now();
console.log(partOne());
console.log(partTwo());
const toc = performance.now();
console.log("TIME: " + ((toc - tic) / 1000).toFixed(6) + " seconds");
