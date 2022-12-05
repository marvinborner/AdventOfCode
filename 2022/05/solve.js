function run(v)
{
	[s,p]=require("fs").readFileSync("input", "utf8").split("\n\n");
	l=s.split("\n").slice(0,-1).map(a=>a.match(/.{1,4}/g))
	s=l[0].map((c,i)=>l.map(r=>r[i])).map(a=>a.filter(b=>b[0]=='['))
	p.split("\n").slice(0,-1).forEach(a=>{b=a.split(" ");w=+b[1];r=+b[3]-1;t=+b[5]-1;p=s[r].slice(0,w);if(!(v%2))p.reverse();s[t]=[...p,...s[t]];s[r].splice(0,w);});
	return s.map(a=>a[0]).join("");
}

const tic = performance.now();
console.log(run(9000));
console.log(run(9001));
const toc = performance.now();
console.log("TIME: " + ((toc - tic) / 1000).toFixed(6) + " seconds");

