const { _, performance } = require("perf_hooks");
const fs = require("fs");
const d = fs.readFileSync("input", "utf8").split("\n");

function partOne() {
c=" (contains ";f=d.map(x=>({i:x.split(c)[0].split(" "),a:x.split(c)[1].split(")")[0].split(", ")}));a=new Map();for(g of f)for(b of g.a)a.set(b,new Set(a.get(b)?[...g.i].filter(x=>a.get(b).has(x)):g.i));return f.map(x=>x.i).flat().filter(x=>!new Set([...a.values()].reduce((a,b)=>[...a,...b],[])).has(x)).length;
}

const tic = performance.now();
console.log(partOne());
//console.log(partTwo());
const toc = performance.now();
console.log("TIME: " + ((toc - tic) / 1000).toFixed(6) + " seconds");
