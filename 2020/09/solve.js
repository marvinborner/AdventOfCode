const { _, performance } = require("perf_hooks");
const fs = require("fs");
const data = fs
  .readFileSync("input", "utf8")
  .split("\n")
  .map((x) => parseInt(x));

function partOne() {
  for (var i = 25; i < data.length; i++) {
    const prev = data.slice(i - 25, i);
    let correct = false;
    for (let x = 0; x < prev.length; x++) {
      for (let y = 0; y < prev.length; y++) {
        if (prev[x] + prev[y] === data[i]) {
          correct = true;
          break;
        }
      }
      if (correct) break;
    }

    if (!correct) return data[i];
  }
  return 0;
}

function partTwo(num) {
  for (let i = 0; i < data.length; i++) {
    let cnt = 0;
    let j = i;
    for (; j < data.length; j++) {
      cnt += data[j];
      if (cnt >= num) break;
    }
    if (cnt == num) {
      const range = data.slice(i, j + 1);
      return Math.min(...range) + Math.max(...range);
    } else {
      cnt = 0;
    }
  }
}

const tic = performance.now();
const num = partOne();
console.log(num);
console.log(partTwo(num));
const toc = performance.now();
console.log("TIME: " + ((toc - tic) / 1000).toFixed(6) + " seconds");
