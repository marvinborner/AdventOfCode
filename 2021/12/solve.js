const { _, performance } = require("perf_hooks");
const fs = require("fs");
const f = fs.readFileSync("input", "utf8").split("\n");

function solve() {
    const t = {};
    f.forEach((l) => {
        let [s, d] = l.split("-");
        if (!s || !d) return;
        t[s] = (t[s] || []).concat([d]);
        t[d] = (t[d] || []).concat([s]);
    });

    // Lol
    one=(n="start",f=new Set())=>n[2]=='d'||t[n].reduce((p,c)=>p+(f.has(c)?0:one(c,n==n.toLowerCase()?new Set([...f,n]):f)),0);
    two=(n="start",f=new Set(),u=false)=>n[2]=='d'||t[n].reduce((p,c)=>p+((c[2]=='a'||(f.has(c)&&u))?0:two(c,n==n.toLowerCase()?new Set([...f,n]):f,f.has(c)||u)),0);

    console.log(one(), two());
}

const tic = performance.now();
solve();
const toc = performance.now();
console.log("TIME: " + ((toc - tic) / 1000).toFixed(6) + " seconds");
