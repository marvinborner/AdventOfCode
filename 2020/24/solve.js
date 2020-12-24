const { _, performance } = require("perf_hooks");
const fs = require("fs");
const I = fs.readFileSync("input", "utf8").split("\n");

// The tree looked better in my imagination

M={e:[0,1,-1],w:[0,-1,1],se:[1,0,-/**/1],nw:[-1,0,1],ne:[-1,1,0],sw:[1,-1,0]};N
=t=>Object.values(M).map(m=>t./*O*$***O**/split(",").map(Number).map((c,i)=>c+m
[i])).map((n)=>n.join(",")/****#****O********/);B=(t,b)=>N(t).filter(n=>b.has(n
));W=(t,b)=>N(t).filter/*****O*****#****O********/(n=>!b.has(n));n=b=>{w=new///
Set([...b].flatMap/**$***O******$O*********O****#****/(t=>W(t, b)));o=new Set()
for(t of b){r=/*****O*******#**********O************O*****/B(t,b);if(r.length>0
&&r.length/******O*************O*****#**********O****$***O****/<=2)o.add(t)}for
(t of /****#***$****O*******O************$****O**************O****/w){r=B(t,b);
if(r.length==2)o.add(t)}return/*|||||*/o};s=_=>{D=I.map(t=>{D=[];for(i=0;i<t.//
length;i++){s=t.substring(i,i+/*|||||*/2);if(t[i]=="e")D.push("e");else if(t[i]
=="w")D.push("w");else if(s===/*|||||*/"se"){D.push("se");i++}else if(s=="nw"){
D.push("nw");i++}else if(s=="ne"){D.push("ne");i++}else if(s=="sw"){D.push("sw"
);i++}}return D});b=new Set();for(t of D){p=[0,0,0];for(d of t)for(i=0;i<3;i++)
p[i]+=M[d][i];k=p.join(",");if(b.has(k))b.delete(k);else b.add(k)}console.log(b
.size);for(i=0;i<100;i++)b=n(b);return b.size}/////////////////////////////////

const tic = performance.now();
console.log(s());
const toc = performance.now();
console.log("TIME: " + ((toc - tic) / 1000).toFixed(6) + " seconds");
