#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"
#include <pthread.h>
#include <my_timing.h>

typedef struct {
    Pixel *src;
    int start;
    int end;
} ThreadData;

static inline void colorize_pixel(Pixel *p) {
    p->r = p->r > 128 ? (220 + p->r)/2 : (30 + p->r)/2;
    p->g = p->g > 128 ? (220 + p->g)/2 : (30 + p->g)/2;
    p->b = p->b > 128 ? (220 + p->b)/2 : (30 + p->b)/2;
}

void *process_pixels_parallel(void *arg) {
    ThreadData *d = (ThreadData*)arg;
    for (int i = d->start; i < d->end; i++) {
        colorize_pixel(&d->src[i]);
    }
    return NULL;
}

void process_pixels_serial(Pixel *src, int total) {
    for (int i = 0; i < total; i++) {
        colorize_pixel(&src[i]);
    }
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s <image.ppm> [threads=1|2|4]\n", argv[0]);
        return -1;
    }

    int threads = 1;
    int repeat = 1;

    if (argc >= 3) threads = atoi(argv[2]);
    if (argc >= 4) repeat = atoi(argv[3]);

    if (threads != 1 && threads != 2 && threads != 4) {
        printf("threads: 1, 2, 4\n");
        return -1;
    }

    if (repeat < 1) repeat = 1;

    int rows, cols, colors;
    Pixel *src = ppm_read(&rows, &cols, &colors, argv[1]);

    if (!src) {
        printf("Unable to read file %s\n", argv[1]);
        return -1;
    }

    int total = rows * cols;

    printf("image: %s (%d x %d)\n", argv[1], rows, cols);
    printf("threads: %d\n", threads);

    double start = get_time_sec();

    for (int r = 0; r < repeat; r++) {
        if (threads == 1) {
            process_pixels_serial(src, total);
        } else {
            pthread_t tid[4];
            ThreadData td[4];
            int chunk = total / threads;

            for (int t = 0; t < threads; t++) {
                td[t].src = src;
                td[t].start = t * chunk;
                td[t].end = (t == threads - 1) ? total : (t + 1) * chunk;
                pthread_create(&tid[t], NULL, process_pixels_parallel, &td[t]);
            }

            for (int t = 0; t < threads; t++) {
                pthread_join(tid[t], NULL);
            }
        }
    }

    double end = get_time_sec();

    printf("total time: %.6f secs\n", end - start);

    ppm_write(src, rows, cols, colors, "output.ppm");
    free(src);

    return 0;
}
