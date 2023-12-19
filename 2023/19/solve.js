const fs = require("fs");
let [workflows, parts] = fs.readFileSync("input", "utf8").trim().split("\n\n");
workflows = workflows.split("\n").map((l) => [l.split("{")[0], l .split("{")[1] .slice(0, -1).split(",").map((w) => w.split(":"))]);
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

let part2 = 0
