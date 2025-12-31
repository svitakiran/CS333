/*
 * Impelement a word counter that can count the number of occurences of every word
 * in a text file in Go
 * 
 * Svita Kiran
 * 11/13/2025
 * CS333
*/

package main

import (
	"fmt"
	"strings"
	"bufio"
	"os"
	"regexp"
	"sort"
)

func main() {
	file, _ := os.Open(os.Args[1])
    defer file.Close()

    counts := make(map[string]int)
    re := regexp.MustCompile(`[^\w']+`)

    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        line := strings.ToLower(scanner.Text())
        line = re.ReplaceAllString(line, " ")
        for _, w := range strings.Fields(line) {
            counts[w]++
        }
    }

    type pair struct{ word string; count int }
    pairs := make([]pair, 0, len(counts))
    for w, c := range counts {
        pairs = append(pairs, pair{w, c})
    }

    sort.Slice(pairs, func(i, j int) bool { return pairs[i].count > pairs[j].count })

    for i := 0; i < len(pairs) && i < 20; i++ {
        fmt.Printf("%-10s %d\n", pairs[i].word, pairs[i].count)
    }
}