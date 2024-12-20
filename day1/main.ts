import fs from "node:fs";
function start() {
	const input = fs.readFileSync("input.txt", { encoding: "ascii" });
	const lines = input.split(/\r?\n/);
	lines.pop();
	const arr1: number[] = [];
	const arr2: number[] = [];
	lines.forEach((line) => {
		const nums = line.split(/\s+/);
		arr1.push(parseInt(nums[0]));
		arr2.push(parseInt(nums[1]));
	});
	console.log(answer1(arr1, arr2));
	console.log(answer2(arr1, arr2));
}
function answer1(l1: number[], l2: number[]): number {
	l1.sort();
	l2.sort();
	let sum = 0;
	for (const idx in l1) {
		sum += Math.abs(l1[idx] - l2[idx]);
	}
	return sum;
}
function answer2(l1: number[], l2: number[]): number {
	const set = new Set(l1.sort());
	return set.values().reduce(
		(prev, current) =>
			prev + current * l2.filter((num) => num === current).length,
		0,
	);
}
start();
