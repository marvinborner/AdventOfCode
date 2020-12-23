const { _, performance } = require("perf_hooks");
const fs = require("fs");
const D = fs.readFileSync("input", "utf8").split("\n")[0].split("").map(Number);

// Yeeehaw
P=(I,C,M)=>{c=new Uint32Array(C+1).map((_,i)=>i+1);for(i=0;i<c.length;i++)c[I[i]]=I[(i+1)%I.length];c[0]=I[0];if(C>I.length){c[I[I.length-1]]=I.length+1;c[c.length-1]=I[0]}for(m=1;m<=M;m++){p=[c[c[0]],c[c[c[0]]],c[c[c[c[0]]]]];d=c[0]-1||C;while(p.includes(d))d=d-1||C;c[c[0]]=c[p[2]];c[p[2]]=c[d];c[d]=p[0];c[0]=c[c[0]]}return c};O=()=>{C=P(D,9,100);r=[];c=C[1];while(c!=1){r.push(c);c=C[c]}return +r.join("")};T=()=>{C=P(D,1e6,1e7);return C[1]*C[C[1]]}

const tic = performance.now();
console.log(O());
console.log(T());
const toc = performance.now();
console.log("TIME: " + ((toc - tic) / 1000).toFixed(6) + " seconds");
