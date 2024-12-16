from functools import reduce


def answer(list1: list[int], list2: list[int]):
    list1.sort()
    list2.sort()
    return reduce(lambda x, y: x + abs(y[0] - y[1]), zip(list1, list2), 0)


def start():
    l1, l2 = [], []
    with open("input1.txt", "r") as f:
        data = f.read()
        for pair in [line.split("   ") for line in data.splitlines()]:
            num1, num2 = int(pair[0]), int(pair[1])
            l1.append(num1)
            l2.append(num2)
    return answer(l1, l2)


if __name__ == "__main__":
    print(start())
