/**
 * Impelementing parallel version of benford's law
 * 
 * Svita Kiran
 * 12/5/2025
 * CS333
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include "my_timing.h"
#include <time.h>

#define NUM_THREADS 8

int DATA_SIZE;
double *data_array;

int counts_global_lock[10];
int counts_per_digit_lock[10];
int counts_local_merge[10];
int counts_local_digit_locks[10];
int counts_thread_slice[NUM_THREADS*10];
int counts_digit_slice[10*NUM_THREADS];

pthread_mutex_t global_mutex;
pthread_mutex_t digit_mutexes[10];
pthread_mutex_t merge_mutex;
pthread_mutex_t local_digit_mutexes[10];

typedef struct { int thread_id; } thread_arg_t;

int leading_digit(double x) {
    x = fabs(x);
    while (x >= 10.0) x /= 10.0;
    while (x > 0 && x < 1.0) x *= 10.0;
    return (int)x;
}

void compute_thread_range(int tid, int *start, int *end) {
    int base = DATA_SIZE / NUM_THREADS;
    int rem = DATA_SIZE % NUM_THREADS;
    *start = tid * base + (tid < rem ? tid : rem);
    *end = *start + base + (tid < rem ? 1 : 0);
}

int load_data(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return -1;
    if (fread(&DATA_SIZE, sizeof(int), 1, fp) != 1) { fclose(fp); return -1; }
    data_array = malloc(sizeof(double)*DATA_SIZE);
    if (!data_array) { fclose(fp); return -1; }
    if (fread(data_array, sizeof(double), DATA_SIZE, fp) != (size_t)DATA_SIZE) { free(data_array); fclose(fp); return -1; }
    fclose(fp);
    return 0;
}

double current_time_seconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC,&ts);
    return ts.tv_sec + ts.tv_nsec*1e-9;
}

// sequential version
double run_sequential(int seq_counts[10]) {
    memset(seq_counts,0,sizeof(int)*10);
    double t0 = current_time_seconds();
    for(int i=0;i<DATA_SIZE;i++){
        int d = leading_digit(data_array[i]);
        if(d>=0 && d<=9) seq_counts[d]++;
    }
    double t1 = current_time_seconds();
    printf("\nsequential counts:\n");
    for(int i=0;i<10;i++) printf("%d: %d\n",i,seq_counts[i]);
    printf("sequential time: %.6f s\n", t1-t0);
    return t1-t0;
}

// worker functions
void* worker_global_lock(void *arg){
    int tid = ((thread_arg_t*)arg)->thread_id;
    int start,end; compute_thread_range(tid,&start,&end);
    for(int i=start;i<end;i++){
        int d = leading_digit(data_array[i]);
        if(d<0||d>9) continue;
        pthread_mutex_lock(&global_mutex);
        counts_global_lock[d]++;
        pthread_mutex_unlock(&global_mutex);
    }
    return NULL;
}

void* worker_per_digit_lock(void *arg){
    int tid = ((thread_arg_t*)arg)->thread_id;
    int start,end; compute_thread_range(tid,&start,&end);
    for(int i=start;i<end;i++){
        int d = leading_digit(data_array[i]);
        if(d<0||d>9) continue;
        pthread_mutex_lock(&digit_mutexes[d]);
        counts_per_digit_lock[d]++;
        pthread_mutex_unlock(&digit_mutexes[d]);
    }
    return NULL;
}

void* worker_local_merge(void *arg){
    int tid = ((thread_arg_t*)arg)->thread_id;
    int start,end; compute_thread_range(tid,&start,&end);
    int local[10]; memset(local,0,sizeof(local));
    for(int i=start;i<end;i++){
        int d = leading_digit(data_array[i]);
        if(d>=0 && d<=9) local[d]++;
    }
    pthread_mutex_lock(&merge_mutex);
    for(int d=0;d<10;d++) counts_local_merge[d]+=local[d];
    pthread_mutex_unlock(&merge_mutex);
    return NULL;
}

void* worker_local_digit_locks(void *arg){
    int tid = ((thread_arg_t*)arg)->thread_id;
    int start,end; compute_thread_range(tid,&start,&end);
    int local[10]; memset(local,0,sizeof(local));
    for(int i=start;i<end;i++){
        int d = leading_digit(data_array[i]);
        if(d>=0 && d<=9) local[d]++;
    }
    for(int d=0;d<10;d++){
        if(local[d]==0) continue;
        pthread_mutex_lock(&local_digit_mutexes[d]);
        counts_local_digit_locks[d]+=local[d];
        pthread_mutex_unlock(&local_digit_mutexes[d]);
    }
    return NULL;
}

void* worker_thread_slice(void *arg){
    int tid = ((thread_arg_t*)arg)->thread_id;
    int start,end; compute_thread_range(tid,&start,&end);
    int *slice = &counts_thread_slice[tid*10];
    memset(slice,0,sizeof(int)*10);
    for(int i=start;i<end;i++){
        int d = leading_digit(data_array[i]);
        if(d>=0 && d<=9) slice[d]++;
    }
    return NULL;
}

void* worker_digit_slice(void *arg){
    int tid = ((thread_arg_t*)arg)->thread_id;
    int start,end; compute_thread_range(tid,&start,&end);
    for(int d=0;d<10;d++) counts_digit_slice[d*NUM_THREADS+tid]=0;
    for(int i=start;i<end;i++){
        int d = leading_digit(data_array[i]);
        if(d>=0 && d<=9) counts_digit_slice[d*NUM_THREADS+tid]++;
    }
    return NULL;
}

// run parallel version
double run_parallel(void* (*worker)(void*), int results[10], pthread_mutex_t locks[], const char *label){
    memset(results,0,sizeof(int)*10);
    pthread_t threads[NUM_THREADS];
    thread_arg_t args[NUM_THREADS];
    if(locks) for(int i=0;i<10;i++) pthread_mutex_init(&locks[i],NULL);
    pthread_mutex_init(&merge_mutex,NULL);

    double t0 = current_time_seconds();
    for(int t=0;t<NUM_THREADS;t++){ args[t].thread_id=t; pthread_create(&threads[t],NULL,worker,&args[t]); }
    for(int t=0;t<NUM_THREADS;t++) pthread_join(threads[t],NULL);
    if(locks) for(int i=0;i<10;i++) pthread_mutex_destroy(&locks[i]);
    pthread_mutex_destroy(&merge_mutex);

    printf("\n%s counts:\n",label);
    for(int i=0;i<10;i++) printf("%d: %d\n",i,results[i]);
    double t1 = current_time_seconds();
    printf("%s time: %.6f s\n",label,t1-t0);
    return t1-t0;
}

int main(int argc,char **argv){
    if(argc<2){ fprintf(stderr,"usage: %s datafile\n",argv[0]); return 1; }
    if(load_data(argv[1])!=0){ fprintf(stderr,"Failed to load %s\n",argv[1]); return 1; }

    int seq_counts[10];
    run_sequential(seq_counts);

    run_parallel(worker_global_lock, counts_global_lock, NULL,"global - single mutex");
    run_parallel(worker_per_digit_lock, counts_per_digit_lock, digit_mutexes,"global - array of mutexes");
    run_parallel(worker_local_merge, counts_local_merge, NULL,"local - single mutex");
    run_parallel(worker_local_digit_locks, counts_local_digit_locks, local_digit_mutexes,"local - array of mutexes");
    run_parallel(worker_thread_slice, counts_thread_slice, NULL,"thread - no mutex");
    run_parallel(worker_digit_slice, counts_digit_slice, NULL,"digit - no mutex");

    free(data_array);
    return 0;
}
