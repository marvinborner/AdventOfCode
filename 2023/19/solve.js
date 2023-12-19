const fs = require("fs");
let [workflows, parts] = fs.readFileSync("input", "utf8").trim().split("\n\n");
workflows = workflows.split("\n").map((l) => [l.split("{")[0], l.split("{")[1].slice(0, -1).split(",").map((w) => w.split(":"))]);
parts = parts.split("\n").map((l) => l.slice(1, -1));

const findWorkflow = (name) => workflows.filter(([n, _]) => name == n)[0][1];

let part1 = 0;
for (const part of parts) {
  eval(part);
  let workflow = "in";
  while (workflow != "A" && workflow != "R") {
    const rules = findWorkflow(workflow);
    for (const rule of rules) {
      if (rule.length == 1) {
        workflow = rule[0];
        break;
      } else if (eval(rule[0]) == true) {
        workflow = rule[1];
        break;
      }
    }
  }
  if (workflow == "A") part1 += x + m + a + s;
}
console.log(part1);

const rec = (name, ranges) => {
  if (name == "R") return 0;
  if (name == "A") return Object.values(ranges).map(([lo, hi]) => Math.max(0, hi - lo - 1)).reduce((a, b) => a * b, 1);

  let res = 0;
  const rules = findWorkflow(name);
  for (const rule of rules) {
    if (rule.length == 1) {
      res += rec(rule[0], ranges);
    } else {
      const [v, cmp, ..._n] = rule[0];
      const n = +_n.join("");

      let aah = structuredClone(ranges);
      if (cmp == ">") {
        const huh = Math.max(aah[v][0], n);
        aah[v][0] = huh;
        res += rec(rule[1], aah);
        ranges[v][1] = huh + 1;
      } else if (cmp == "<") {
        const huh = Math.min(aah[v][1], n);
        aah[v][1] = huh;
        res += rec(rule[1], aah);
        ranges[v][0] = huh - 1;
      }
    }
  }

  return res;
};

console.log(
  rec("in", { x: [0, 4001], m: [0, 4001], a: [0, 4001], s: [0, 4001] }),
);
