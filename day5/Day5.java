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
			// TODO: handle exception
			e.printStackTrace();
		}

		System.out.println(answer1(ruleMap, seq));
		System.out.println(answer2(ruleMap, seq));
	}

	private static boolean valid(List<Integer> list, Map<Integer, List<Integer>> rules) {
		for (int i = 0; i < list.size() - 1; i++) {
			int num = list.get(i);
			if (!rules.containsKey(num) || !rules.get(num).contains(list.get(i + 1)))
				return false;
		}
		return true;
	}

	private static int getMiddleNumber(List<Integer> l) {
		return l.get(l.size() / 2);
	}

	private static int answer1(Map<Integer, List<Integer>> ruleMap, List<List<Integer>> seq) {
		return seq.stream().filter(l -> valid(l, ruleMap)).mapToInt(Day5::getMiddleNumber).sum();
	}

	private static int answer2(Map<Integer, List<Integer>> ruleMap, List<List<Integer>> sequence) {
		return sequence.stream().filter(s -> !valid(s, ruleMap)).mapToInt(seq -> {
			List<Integer> fixed = new ArrayList<>();
			int size = seq.size();

			for (int i = 0; fixed.size() != size; i = (i + 1) % size) {
				int num = seq.get(i);
				if (fixed.contains(num))
					continue;

				List<Integer> rule = ruleMap.get(num);
				if (rule == null || rule.stream().allMatch(j -> !(fixed.contains(j) ^ seq.contains(j))))
					fixed.add(num);
			}

			return getMiddleNumber(fixed);
		}).sum();
	}
}
