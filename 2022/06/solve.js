d=require("fs").readFileSync("input", "utf8").split("")

function solve(k)
{
	return d.map((_,i)=>d.slice(i,i+k)).findIndex(a=>(new Set(a)).size==a.length)+k
}

const tic = performance.now();
console.log(solve(4));
console.log(solve(14));
const toc = performance.now();
console.log("TIME: " + ((toc - tic) / 1000).toFixed(6) + " seconds");
