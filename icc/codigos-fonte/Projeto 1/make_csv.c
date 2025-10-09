#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define _POSIX_C_SOURCE 200809L
typedef struct { int peso; int valor; } Item;

int forca_bruta(Item* itens, int n, int capacidade);
int algoritmo_guloso(Item* itens, int n, int capacidade);
int programacao_dinamica(Item* itens, int n, int capacidade);

static long long now_ns(void){
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

static void gen_items(Item* A, int n, unsigned seed){
    srand(seed);
    for (int i=0;i<n;i++){
        A[i].peso  = 1 + rand()%100;
        A[i].valor = 1 + rand()%100;
    }
}

static void copy_items(Item* dst, const Item* src, int n){
    memcpy(dst, src, n * sizeof(Item));
}

int main(void){
    int W = 1000;
    unsigned seed = 1;
    int ns[] = {5,8,10,12,14,16,18,20,22,24,25,26,27,28,29,30,35,40,45,50};
    int k = sizeof(ns)/sizeof(ns[0]);

    printf("n,W,method,time_ms,best_value\n");

    for (int idx = 0; idx < k; ++idx){
        int n = ns[idx];
        Item* base = (Item*)malloc(sizeof(Item)*n);
        gen_items(base, n, seed);

        if (n <= 30){
            Item* A = (Item*)malloc(sizeof(Item)*n);
            copy_items(A, base, n);
            long long t0 = now_ns();
            int val = forca_bruta(A, n, W);
            long long t1 = now_ns();
            double time_ms = (t1 - t0)/1e6;
            
            // Se demorar mais de 60 segundos, marca como timeout
            if (time_ms > 60000) {
                printf("%d,%d,bf,TIMEOUT,%d\n", n, W, val);
            } else {
                printf("%d,%d,bf,%.3f,%d\n", n, W, time_ms, val);
            }
            free(A);
        } else {
            printf("%d,%d,bf,NA,NA\n", n, W);
        }

        {
            Item* A = (Item*)malloc(sizeof(Item)*n);
            copy_items(A, base, n);
            long long t0 = now_ns();
            int val = algoritmo_guloso(A, n, W);
            long long t1 = now_ns();
            printf("%d,%d,greedy,%.3f,%d\n", n, W, (t1 - t0)/1e6, val);
            free(A);
        }

        {
            Item* A = (Item*)malloc(sizeof(Item)*n);
            copy_items(A, base, n);
            long long t0 = now_ns();
            int val = programacao_dinamica(A, n, W);
            long long t1 = now_ns();
            printf("%d,%d,dp,%.3f,%d\n", n, W, (t1 - t0)/1e6, val);
            free(A);
        }

        free(base);
    }
    return 0;
}
