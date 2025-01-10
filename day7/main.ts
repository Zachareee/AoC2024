import { readFileSync } from "node:fs";
type Input = [number, number[]][];
type Op = (sum: number, value: number, op: (num: number) => boolean) => boolean;
function answer1(map: Input): number {
	return sum(map, [sub, div]);
}
function answer2(map: Input): number {
	return sum(map, [sub, div, scat]);
}
const sub: Op = (sum: number, value: number, op: (num: number) => boolean) => {
	const sub = sum - value;
	return sub >= 0 && op(sub);
};
const div: Op = (sum: number, value: number, op: (num: number) => boolean) => {
	const div = sum / value;
	return div % 1 == 0 && op(div);
};
const scat: Op = (sum: number, value: number, op: (num: number) => boolean) => {
	// need +0.1 for cases where number is power of 10 so that we
	// take the right remainder e.g. if value is 10, rounded will
	// divide by 10 instead of 100 (1 digit more for comparison)
	const rounded = 10 ** Math.ceil(Math.log10(value + 0.1));
	return sum % rounded == value && op(Math.floor(sum / rounded));
};
function sum(map: Input, ops: Op[]) {
	return map.filter(([sum, values]) => {
		function branch(idx: number, sum: number): boolean {
			const value = values[idx];
			if (idx == 0) return sum == value;
			return ops.some((f) =>
				f(sum, value, (num) => branch(idx - 1, num))
			);
		}
		return branch(values.length - 1, sum);
	}).map((tup) => tup[0]).reduce((n1, n2) => n1 + n2, 0);
}
function start() {
	const input: Input = readFileSync("input.txt", { encoding: "ascii" })
		.split(/\r?\n/).filter((str) => str)
		.map((str) => str.split(/:/))
		.map(([sum, nums]) => [
			parseInt(sum),
			nums.split(" ").filter((str) => str).map((num) =>
				parseInt(num)
			),
		]);
	console.log(answer1(input));
	console.log(answer2(input));
}
start();
