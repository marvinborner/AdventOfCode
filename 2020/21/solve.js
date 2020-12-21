const { _, performance } = require("perf_hooks");
const fs = require("fs");
const data = fs.readFileSync("input", "utf8").split("\n");

function partOne() {
  const foods = data.map((x) => ({
    ingredients: x.split(" (contains ")[0].split(" "),
    allergens: x.split(" (contains ")[1].split(")")[0].split(", "),
  }));

  const allergens = new Map();
  for (let food of foods) {
    for (let allergen of food.allergens) {
      const prev = allergens.get(allergen);
      let matching;
      if (prev)
        matching = new Set([...food.ingredients].filter((x) => prev.has(x)));
      else matching = new Set(food.ingredients);
      allergens.set(allergen, matching);
    }
  }
  const all = foods.map((x) => x.ingredients).flat();
  const matching = [
    ...new Set([...allergens.values()].reduce((a, b) => [...a, ...b], [])),
  ];
  return all.filter((x) => !matching.includes(x)).length;
}

const tic = performance.now();
console.log(partOne());
//console.log(partTwo());
const toc = performance.now();
console.log("TIME: " + ((toc - tic) / 1000).toFixed(6) + " seconds");
