import java.io.File;
import java.util.*;
import java.util.stream.Stream;

public class Day5 {
	public static void main(String[] args) {
		File file = new File("input.txt");

		List<List<Integer>> rules = new ArrayList<>();
		List<List<Integer>> seq = new ArrayList<>();
		try (Scanner sc = new Scanner(file)) {
			while (sc.hasNext("\\d+\\|\\d+")) {
				rules.add(Stream.of(sc.nextLine().split("\\|"))
						.map(Integer::parseInt)
						.toList());
			}
			while (sc.hasNext()) {
				seq.add(Stream.of(sc.next().split(",")).map(Integer::parseInt).toList());
			}
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}
		System.out.println(answer1(rules, seq));
	}

	private static boolean valid(List<Integer> list, Map<Integer, List<Integer>> rules) {
		for (int i = 0; i < list.size() - 1; i++) {
			int num = list.get(i);
			if (!rules.containsKey(num) || !rules.get(num).contains(list.get(i + 1)))
				return false;
		}
		return true;
	}

	private static int answer1(List<List<Integer>> rules, List<List<Integer>> seq) {
		Map<Integer, List<Integer>> ruleMap = new HashMap<>();
		rules.forEach(l -> {
			int key = l.get(0);
			List<Integer> innerList = ruleMap.getOrDefault(key, new ArrayList<>());
			innerList.add(l.get(1));
			ruleMap.put(key, innerList);
		});

		return seq.stream().mapToInt(l -> valid(l, ruleMap) ? l.get(l.size() / 2) : 0).sum();
	}
}
