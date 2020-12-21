const { _, performance } = require("perf_hooks");
const fs = require("fs");
const d = fs.readFileSync("input", "utf8").split("\n");

const tic = performance.now();

// YAYY
(()=>{c=" (contains ";f=d.map(x=>({i:x.split(c)[0].split(" "),a:x.split(c)[1].split(")")[0].split(", ")}));a=new Map();for(g of f)for(b of g.a)a.set(b,new Set(a.get(b)?[...g.i].filter(x=>a.get(b).has(x)):g.i));console.log(f.map(x=>x.i).flat().filter(x=>!new Set([...a.values()].reduce((a,b)=>[...a,...b],[])).has(x)).length);o=Array.from(a,([b,i])=>({b,i}));let n;do{n=!1;for(b of o)if(b.i.size>1){b.i=new Set([...b.i].filter(x=>!o.filter(x=>x.i.size==1).map(x=>[...x.i][0]).includes(x)));n=!0}}while(n)console.log(o.sort((a,b)=>a.b.localeCompare(b.b)).map(x=>[...x.i][0]).join(','))})()

const toc = performance.now();
console.log("TIME: " + ((toc - tic) / 1000).toFixed(6) + " seconds");
