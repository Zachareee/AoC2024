import java.io.File;
import java.util.*;
import java.util.stream.Stream;

public class Day5 {
	public static void main(String[] args) {
		File file = new File("input.txt");

		List<List<Integer>> seq = new ArrayList<>();
		Map<Integer, List<Integer>> ruleMap = new HashMap<>();

		try (Scanner sc = new Scanner(file)) {
			while (sc.hasNext("\\d+\\|\\d+")) {
				int arr[] = Stream.of(sc.nextLine().split("\\|")).mapToInt(Integer::parseInt).toArray();

				int key = arr[0];
				List<Integer> innerList = ruleMap.getOrDefault(key, new ArrayList<>());
				innerList.add(arr[1]);
				ruleMap.put(key, innerList);
			}
			while (sc.hasNext()) {
				seq.add(Stream.of(sc.next().split(",")).map(Integer::parseInt).toList());
			}
		} catch (Exception e) {
		}

		System.out.println(answer1(ruleMap, seq));
		System.out.println(answer2(ruleMap, seq));
	}

	private static boolean valid(List<Integer> list, Map<Integer, List<Integer>> rules) {
		int size = list.size();
		for (int i = 0; i < size; i++) {
			int num = list.get(i);
			if (list.reversed().stream().skip(size - i)
					.anyMatch(x -> rules.containsKey(num) && rules.get(num).contains(x)))
				return false;
		}
		return true;
	}

	private static int answer1(Map<Integer, List<Integer>> ruleMap, List<List<Integer>> seq) {
		return seq.stream().filter(l -> valid(l, ruleMap)).mapToInt(l -> l.get(l.size() / 2)).sum();
	}

	private static int ruleMatchCount(Map<Integer, List<Integer>> ruleMap, List<Integer> seq, int num) {
		if (!ruleMap.containsKey(num))
			return 0;
		return (int) ruleMap.get(num).stream().filter(j -> seq.contains(j)).count();
	}

	private static int answer2(Map<Integer, List<Integer>> ruleMap, List<List<Integer>> sequence) {
		// This algorithm assumes that the valid output of the sequence is deterministic
		return sequence.stream().filter(s -> !valid(s, ruleMap)).mapToInt(seq -> seq.stream()
				.sorted((x, y) -> ruleMatchCount(ruleMap, seq, x) - ruleMatchCount(ruleMap, seq, y))
				.skip(seq.size() / 2).findFirst().get()).sum();
	}

}
