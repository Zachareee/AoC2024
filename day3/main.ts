import fs from "node:fs";
function answer1(lines: string[]): number {
  return lines.map((line) =>
    line.matchAll(/mul\((\d{1,3}),(\d{1,3})\)/g)
      .map((match) =>
        match.slice(1).reduce((prev, curr) => prev * parseInt(curr), 1)
      )
      .reduce((prev, curr) => prev + curr)
  ).reduce((prev, curr) => prev + curr);
}
function start() {
  const input = fs.readFileSync("input.txt", { encoding: "ascii" });
  const lines = input.split(/\r?\n/);
  lines.pop();
  console.log(answer1(lines));
}
start();
