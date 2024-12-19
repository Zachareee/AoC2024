package main

import (
	"fmt"
	"math"
	"os"
	"regexp"
	"slices"
	"strconv"
	"strings"
)

type void struct{}

var member void

func main() {
	bytes, err := os.ReadFile("input.txt")

	if err != nil {
		fmt.Println("Error occured, %+v", err)
		return
	}

	newlines := regexp.MustCompile("\\r?\\n")

	lines := newlines.Split(string(bytes), -1)
	l1, l2 := []int{}, []int{}
	var num int

	for _, line := range lines {
		arr := strings.Split(line, "   ")
		if len(arr) == 2 {
			num, _ = strconv.Atoi(arr[0])
			l1 = append(l1, num)

			num, _ = strconv.Atoi(arr[1])
			l2 = append(l2, num)
		}
	}

	fmt.Println(answer1(l1, l2))
	fmt.Println(answer2(l1, l2))
}

func answer1(l1, l2 []int) int {
	slices.Sort(l1)
	slices.Sort(l2)

	var sum int
	for idx := range l1 {
		sum += int(math.Abs(float64(l1[idx] - l2[idx])))
	}
	return sum
}

func answer2(l1, l2 []int) int {
	set := make(map[int]void)
	for _, num := range l1 {
		set[num] = member
	}

	occurrences := make(map[int]int)
	for _, num := range l2 {
		occurrences[num]++
	}

	var sum int
	for k := range set {
		sum += occurrences[k] * k
	}

	return sum
}
