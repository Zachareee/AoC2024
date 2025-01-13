package main

import (
	"fmt"
	"os"
	"regexp"
)

// 380 too high
func answer1(m map[byte][][2]int, size int) int {
	set := make(map[[2]int]int)

	for _, v := range m {
		for _, coord0 := range v {
			for _, coord1 := range v {
				if coord0 == coord1 {
					continue
				}
				if result := antinode(coord0, coord1); valid(result, size) {
					set[result] = 0
				}
			}
		}
	}

	return len(set)
}

func antinode(a, b [2]int) [2]int {
	return [2]int{2*a[0] - b[0], 2*a[1] - b[1]}
}

func valid(coord [2]int, size int) bool {
	for _, value := range coord {
		if value < 0 || value >= size {
			return false
		}
	}
	fmt.Println(coord)
	return true
}

func main() {
	text, err := os.ReadFile("./input.txt")

	if err != nil {
		fmt.Println("Unable to read file")
		return
	}

	newlines := regexp.MustCompile("\\r?\\n")
	lines := newlines.Split(string(text), -1)

	m := make(map[byte][][2]int)
	nodepattern := regexp.MustCompile("([\\d\\w])")

	for i, line := range lines {
		for _, match := range nodepattern.FindAllIndex([]byte(line), -1) {
			coord := [2]int{i, match[0]}
			slice, ok := m[line[match[0]]]
			if ok {
				slice = append(slice, coord)
			} else {
				slice = [][2]int{coord}
			}
			m[line[match[0]]] = slice
		}
	}

	fmt.Println(answer1(m, len(lines)-1))
}
