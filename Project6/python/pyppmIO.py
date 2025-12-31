# Bruce A. Maxwell
# Spring 2018
# PPM IO functions
#
# A simple PPM library for reading and writing color PPMs
#

import sys
import time
from threading import Thread

class PPM:
    def __init__(self, filename=None):
        self.rows = 0
        self.cols = 0
        self.colors = 255
        self.data = bytearray()
        self.source = filename

        if filename is not None:
            self.read(filename)

    def read(self, filename):
        try:
            fp = open(filename, "rb")

            line = fp.readline().strip()
            if line != b"P6":
                print("Unsupported PPM format (expected P6)")
                fp.close()
                return None

            line = fp.readline()
            while line.startswith(b"#"):
                line = fp.readline()

            parts = line.split()
            self.cols = int(parts[0])
            self.rows = int(parts[1])

            self.colors = int(fp.readline().strip())

            self.data = bytearray(fp.read())
            fp.close()
        except Exception as e:
            print("Unable to process file %s: %s" % (filename, e))
            return None

    def write(self, filename):
        with open(filename, "wb") as fp:
            header = "P6\n%d %d\n%d\n" % (self.cols, self.rows, self.colors)
            fp.write(bytearray(header, encoding="utf-8"))
            fp.write(self.data)

    def get(self, row, col):
        index = 3 * (row * self.cols + col)
        return [self.data[index + 0],
                self.data[index + 1],
                self.data[index + 2]]

    def set(self, row, col, r, g, b):
        index = 3 * (row * self.cols + col)
        self.data[index + 0] = r
        self.data[index + 1] = g
        self.data[index + 2] = b

def bold_pixel(r, g, b):
    r = (220 + r) // 2 if r > 128 else (30 + r) // 2
    g = (220 + g) // 2 if g > 128 else (30 + g) // 2
    b = (220 + b) // 2 if b > 128 else (30 + b) // 2
    return r, g, b

def worker(ppm, start_idx, end_idx, repeats):
    cols = ppm.cols
    total = ppm.rows * cols

    for _ in range(repeats):
        for idx in range(start_idx, end_idx):
            row = idx // cols
            col = idx % cols
            r, g, b = ppm.get(row, col)
            nr, ng, nb = bold_pixel(r, g, b)
            ppm.set(row, col, nr, ng, nb)

def main(argv):
    if len(argv) < 3:
        print("Usage: python3 filename input.ppm num_threads")
        print("  num_threads: 1, 2, 4")
        sys.exit(1)

    in_file = argv[1]
    out_file = "mod.ppm"
    num_threads = int(argv[2])
    repeats = 1

    if num_threads not in (1, 2, 4):
        print("num_threads: 1, 2, 4")
        sys.exit(1)

    ppm = PPM(in_file)
    if ppm.data is None or len(ppm.data) == 0:
        print("Failed to read image")
        sys.exit(1)

    total_pixels = ppm.rows * ppm.cols

    start_time = time.perf_counter()

    if num_threads == 1:
        worker(ppm, 0, total_pixels, repeats)
    else:
        threads = []
        for t in range(num_threads):
            start_idx = t * total_pixels // num_threads
            end_idx = (t + 1) * total_pixels // num_threads
            th = Thread(target=worker, args=(ppm, start_idx, end_idx, repeats))
            threads.append(th)
            th.start()
        for th in threads:
            th.join()

    end_time = time.perf_counter()
    elapsed = end_time - start_time

    print(f"threads: {num_threads}, time: {elapsed:.6f} seconds")

    ppm.write("mod.ppm")

if __name__ == "__main__":
    main(sys.argv)
