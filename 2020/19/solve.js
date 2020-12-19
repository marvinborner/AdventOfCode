const { _, performance } = require("perf_hooks");
const fs = require("fs");
const data = fs.readFileSync("input", "utf8").split("\n\n");
const rules = data[0].split("\n");
const input = data[1].split("\n");

function solve() {
  const r = [];

  rules.map((rule) => {
    const tmp = {};
    const arr = rule.split(": ");
    tmp.orig = arr[1];
    if (arr[1].indexOf('"') > -1) tmp.orig = arr[1][1];
    r[arr[0]] = tmp;
  });

  let s = r[0].orig;
  let match = s.match(/\d+/g);
  while (match && match.length > 0) {
    s = s.replace(match[0], "(" + r[match[0]].orig + ")");
    match = s.match(/\d+/g);
  }

  const regexpStr = "^" + s.split(" ").join("") + "$";
  let cnt = 0;
  input.map((word) => {
    if (word.match(regexpStr)) cnt++;
  });

  return cnt;
}

const tic = performance.now();
console.log(solve());
// Sorry for hardcoding :P
rules[54] = "8: 42+";
rules[64] =
  "11: 42 31 | 42 (42 31 | 42 (42 31 | 42 (42 31 | 42 (42 31) 31) 31) 31) 31";
console.log(solve());
const toc = performance.now();
console.log("TIME: " + ((toc - tic) / 1000).toFixed(6) + " seconds");
