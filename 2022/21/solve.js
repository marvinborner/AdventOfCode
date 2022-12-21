d=require("fs").readFileSync("input", "utf8").trimEnd().split("\n").map(s=>s.split(": ")).reduce((a,s)=>({...a,[s[0]]:s[1].split(/ ([+|\-|*|/]) /)}),{})

r=m=>isNaN(d[m])?eval(r(d[m][0])+d[m][1]+r(d[m][2])):d[m]

function part1()
{
	return r("root")
}

function part2()
{
	// small binary search
	// i'm sure there are better ways.. but it works
	d["root"][1] = "-"
	low = 1e2
	high = 1e20
	while (low != high) {
		mid = (low + high)/2
		d["humn"][0] = `${mid}`
		score = 0 - r("root")
		if (score < 0) low = mid
		else if (score == 0) return mid
		else high = mid
	}
	return 0
}

const tic = performance.now();
console.log(part1());
console.log(part2());
const toc = performance.now();
console.log("TIME: " + ((toc - tic) / 1000).toFixed(6) + " seconds");
