import fs from "node:fs";
const add = (num1: number, num2: number) => num1 + num2;
function answer1(line: string): number {
  return line.matchAll(/mul\((\d{1,3}),(\d{1,3})\)/g)
    .map((match) =>
      match.slice(1).reduce((prev, curr) => prev * parseInt(curr), 1)
    )
    .reduce(add, 0);
}
function answer2(lines: string): number {
  return answer1(lines) -
    // find the don't()...do() blocks and subtract them
    lines.match(/don't\(\).*?do\(\)/g)!.map(answer1).reduce(add, 0) -
    // find the unclosed don't() block
    lines.match(/don't\(\)(?!.*do\(\)).*/g)!.map(answer1).reduce(add, 0);
}
function start() {
  const lines = fs.readFileSync("input.txt", { encoding: "ascii" }).replaceAll(
    /\r?\n/g,
    "",
  );
  console.log(answer1(lines));
  console.log(answer2(lines));
}
start();
