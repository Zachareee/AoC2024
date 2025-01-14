package main

import (
	"fmt"
	"os"
	"regexp"
	"strings"
)

type node [2]int
type set map[node]int

func answer1(m map[byte][]node, size int) int {
	return node_aggregator(m, func(a, b node, set set) {
		if result := antinode(a, b); valid(result, size) {
			set[result] = 0
		}
	})
}

func answer2(m map[byte][]node, size int) int {
	return node_aggregator(m, func(a, b node, set set) {
		for _, node := range resonance(a, b, size) {
			set[node] = 0
		}
	})
}

func node_aggregator(m map[byte][]node, f func(node, node, set)) int {
	set := make(map[node]int)
	for _, v := range m {
		for _, coord0 := range v {
			for _, coord1 := range v {
				if coord0 == coord1 {
					continue
				}
				f(coord0, coord1, set)
			}
		}
	}

	return len(set)
}

func antinode(a, b node) node {
	return add_nodes(a, sub_nodes(a, b))
}

func resonance(a, b node, size int) (nodes []node) {
	dist := sub_nodes(a, b)
	nodes = append(nodes, a)
	node := a
	for {
		if node = add_nodes(node, dist); valid(node, size) {
			nodes = append(nodes, node)
		} else {
			break
		}
	}
	return
}

func add_nodes(a, b node) node {
	return node{a[0] + b[0], a[1] + b[1]}
}

func sub_nodes(a, b node) node {
	return node{a[0] - b[0], a[1] - b[1]}
}

func valid(coord node, size int) bool {
	for _, value := range coord {
		if value < 0 || value >= size {
			return false
		}
	}
	return true
}

func main() {
	text, err := os.ReadFile("./eg.txt")

	if err != nil {
		fmt.Println("Unable to read file")
		return
	}

	lines := regexp.MustCompile("\\r?\\n").Split(strings.TrimSpace(string(text)), -1)

	m := make(map[byte][]node)
	nodepattern := regexp.MustCompile("([\\d\\w])")

	for i, line := range lines {
		for _, match := range nodepattern.FindAllIndex([]byte(line), -1) {
			coord := node{i, match[0]}
			slice, ok := m[line[match[0]]]
			if ok {
				slice = append(slice, coord)
			} else {
				slice = []node{coord}
			}
			m[line[match[0]]] = slice
		}
	}

	fmt.Println(answer1(m, len(lines)))
	fmt.Println(answer2(m, len(lines)))
}
