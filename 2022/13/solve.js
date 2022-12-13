d=require("fs").readFileSync("input","utf8").trimEnd().split("\n\n").map(b=>b.split("\n").map(eval))

s=(a,b)=>!b.length&&a.length>0?1:a.length?(l=a[0],r=b[0],a=a.slice(1),b=b.slice(1),l===+l&&r===+r)?l!=r?l-r<0?-1:1:s(a,b):(w=s(l===+l?[l]:l,r===+r?[r]:r))||s(a,b):b.length>0?-1:0;

p1=_=>d.map(l=>s(l[0],l[1])).map((x,i)=>[x,i]).filter(x=>x[0]<0).reduce((a,x)=>a+x[1]+1,0)

p2=_=>(i=[[[2]],[[6]]]).map(e=>[...d.flat(),...i].sort(s).indexOf(e)+1).reduce((a,x)=>a*x);

// non-relevant performance testing
tic = performance.now();
console.log(p1());
console.log(p2());
toc = performance.now();
console.log("TIME: " + ((toc - tic) / 1000).toFixed(6) + " seconds");
