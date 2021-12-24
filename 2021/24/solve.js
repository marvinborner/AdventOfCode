const { _, performance } = require("perf_hooks");
const fs = require("fs");

function solve() {
    n=[],m=[],t=[];
    fs.readFileSync("input", "utf8").split("in").map(b=>b.split("\n")).slice(1).forEach((b,i)=>{if(b[4][6]=='1')t.push([i,+b[15].split(" ").slice(-1)[0]]);else{[j,x]=t.pop();d=x+ +b[5].split(" ").slice(-1)[0];if(d<0)[i,j,d]=[j,i,-d];m[i]=9;m[j]=9-d;n[i]=1+d;n[j]=1}})
    console.log(m.join(""),n.join(""));
}

const tic = performance.now();
solve();
const toc = performance.now();
console.log("TIME: " + ((toc - tic) / 1000).toFixed(6) + " seconds");
