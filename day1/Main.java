import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) {
		File file = new File("input.txt");
		ArrayList<Integer> l1 = new ArrayList<>();
		ArrayList<Integer> l2 = new ArrayList<>();

		try (Scanner sc = new Scanner(file)) {
			while (sc.hasNext()) {
				String arr[] = sc.nextLine().split("\s+");
				l1.add(Integer.parseInt(arr[0]));
				l2.add(Integer.parseInt(arr[1]));
			}
		} catch (Exception e) {
			System.out.println(e);
			return;
		}

		System.out.println(answer1(l1, l2));
		System.out.println(answer2(l1, l2));
	}

	private static int answer1(List<Integer> l1, List<Integer> l2) {
		Collections.sort(l1);
		Collections.sort(l2);

		int sum = 0;

		for (int i = 0; i < l1.size(); i++) {
			sum += Math.abs(l1.get(i) - l2.get(i));
		}

		return sum;
	}

	private static int answer2(List<Integer> l1, List<Integer> l2) {
		Set<Integer> s1 = new HashSet<>(l1);
		Map<Integer, Integer> frequency = new HashMap<>();
		l2.forEach(num -> {
			frequency.merge(num, 1, (f, s) -> f + s);
		});

		return s1.stream().reduce(0, (x, y) -> x + y * frequency.getOrDefault(y, 0), (x, y) -> x + y);
	}
}
