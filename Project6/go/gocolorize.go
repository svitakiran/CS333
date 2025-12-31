package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
	"sync"
	"time"
)

type Pixel struct {
	R, G, B uint8
}

// Read P6 PPM image
func readPPM(filename string) ([]Pixel, int, int, int) {
	file, err := os.Open(filename)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	reader := bufio.NewReader(file)

	// Read header
	magic, _ := reader.ReadString('\n')
	if strings.TrimSpace(magic) != "P6" {
		panic("Not a P6 PPM file")
	}

	// Skip comments
	line, _ := reader.ReadString('\n')
	for strings.HasPrefix(line, "#") {
		line, _ = reader.ReadString('\n')
	}

	// Read width, height
	parts := strings.Fields(line)
	width, _ := strconv.Atoi(parts[0])
	height, _ := strconv.Atoi(parts[1])

	// Read max color
	line, _ = reader.ReadString('\n')
	maxVal, _ := strconv.Atoi(strings.TrimSpace(line))
	if maxVal != 255 {
		panic("Only max color 255 supported")
	}

	// Read binary pixel data
	numPixels := width * height
	data := make([]Pixel, numPixels)
	buf := make([]byte, numPixels*3)
	_, err = reader.Read(buf)
	if err != nil {
		panic(err)
	}

	for i := 0; i < numPixels; i++ {
		data[i] = Pixel{R: buf[i*3], G: buf[i*3+1], B: buf[i*3+2]}
	}

	return data, width, height, maxVal
}

// Write P6 PPM image
func writePPM(filename string, pixels []Pixel, width, height, maxVal int) {
	file, err := os.Create(filename)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	fmt.Fprintf(writer, "P6\n%d %d\n%d\n", width, height, maxVal)
	for _, p := range pixels {
		writer.Write([]byte{p.R, p.G, p.B})
	}
	writer.Flush()
}

// Pixel-wise operator
func processPixels(pixels []Pixel, start, end int) {
	for i := start; i < end; i++ {
		r, g, b := int(pixels[i].R), int(pixels[i].G), int(pixels[i].B)
		if r > 128 {
			r = (220 + r) / 2
		} else {
			r = (30 + r) / 2
		}
		if g > 128 {
			g = (220 + g) / 2
		} else {
			g = (30 + g) / 2
		}
		if b > 128 {
			b = (220 + b) / 2
		} else {
			b = (30 + b) / 2
		}
		pixels[i].R, pixels[i].G, pixels[i].B = uint8(r), uint8(g), uint8(b)
	}
}

func main() {
	if len(os.Args) < 3 {
		fmt.Println("Usage: go run go_colorize_ppm.go <image.ppm> <threads>")
		return
	}

	filename := os.Args[1]
	numThreads := 1
	fmt.Sscanf(os.Args[2], "%d", &numThreads)

	// Read image
	pixels, width, height, maxVal := readPPM(filename)

	// Start timer
	start := time.Now()

	// Parallel processing
	var wg sync.WaitGroup
	chunk := len(pixels) / numThreads
	for t := 0; t < numThreads; t++ {
		startIdx := t * chunk
		endIdx := startIdx + chunk
		if t == numThreads-1 {
			endIdx = len(pixels)
		}
		wg.Add(1)
		go func(s, e int) {
			defer wg.Done()
			processPixels(pixels, s, e)
		}(startIdx, endIdx)
	}
	wg.Wait()
	elapsed := time.Since(start)
	fmt.Printf("threads: %d, time: %f secs\n", numThreads, elapsed.Seconds())

	// Write output
	writePPM("gomod.ppm", pixels, width, height, maxVal)
}