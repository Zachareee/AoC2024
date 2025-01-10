import fs from "node:fs";
type Input = [number, number[]][];
function answer1(map: Input): number {
	return map.filter(check).map((tup) => tup[0]).reduce(
		(n1, n2) => n1 + n2,
		0,
	);
}
function check([sum, values]: [number, number[]]): boolean {
	function op(idx: number, sum: number): boolean {
		if (idx == -1) {
			return sum == 0 || sum == 1;
		}
		const div = sum / values[idx];
		const sub = sum - values[idx];
		if (div % 1) return op(idx - 1, sub);
		if (sub < 0) return op(idx - 1, div);
		return op(idx - 1, sub) || op(idx - 1, div);
	}
	return op(values.length - 1, sum);
}
function start() {
	const input: Input = fs.readFileSync("input.txt", {
		encoding: "ascii",
	}).split(/\r?\n/).filter((str) => str).map((str) => str.split(/:/)).map(
		(
			[sum, nums],
		) => [
			parseInt(sum),
			nums.split(" ").filter((str) => str).map((num) =>
				parseInt(num)
			),
		],
	);
	console.log(answer1(input));
}
start();
