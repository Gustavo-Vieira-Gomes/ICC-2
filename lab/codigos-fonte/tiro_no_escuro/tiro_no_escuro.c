#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(int v[], int ini, int fim) {
    int pivo = v[(ini + fim) / 2], i = ini, j = fim;

    while(j >= i) {
        while(v[i] < pivo)
            i++;

        while(v[j] > pivo)
            j--;

        if(j >= i) {
            swap(&v[i], &v[j]);
            i++;
            j--;
        }
    }

    if(ini < j) quick_sort(v, ini, j);
    if(i < fim) quick_sort(v, i, fim);
}

void merge(int v[], int ini, int meio, int fim) {
    int n1, n2;

    n1 = meio - ini + 1;
    n2 = fim - meio;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    
    for(int i = 0; i < n1; i++) {
        L[i] = v[ini + i];
    }

    for(int i = 0; i < n2; i++) {
        R[i] = v[meio + 1 + i];
    }

    int i = 0, j = 0;
    for(int k = ini; k <= fim; k++) {
        if(i >= n1) {
            v[k] = R[j];
            j++;
        } else if(j >= n2) {
            v[k] = L[i];
            i++;
        } else if(L[i] <= R[j]) {
            v[k] = L[i];
            i++;
        } else{
            v[k] = R[j];
            j++;
        }
    }

    free(L);
    free(R);
}

void merge_sort(int v[], int ini, int fim) {
    if(ini < fim) {
        int meio = ini + (fim - ini) / 2;
        merge_sort(v, ini, meio);
        merge_sort(v, meio + 1, fim);
        merge(v, ini, meio, fim);
    }
}

void counting_sort(int v[], int N) {
    int min = v[0], max = v[0];
    for(int i = 0; i < N; i++) {
        if(v[i] < min) {
            min = v[i];
        }
        if(v[i] > max) {
            max = v[i];
        }
    }

    int range = max - min + 1;
    int *aux = (int *)calloc(range, sizeof(int));

    for(int i = 0; i < N; i++) {
        aux[v[i] - min]++;
    }

    int j = 0;
    for(int i = 0; i < range; i++) {
        while(aux[i] != 0) {
            v[j] = i + min;
            j++;
            aux[i]--;
        }
    }

    free(aux);
}

int main() {
    int N, metodo;
    char caso[20];

    scanf("%d", &N);

    scanf("%s", caso);

    scanf("%d", &metodo);

    int *sequencia = (int *)malloc(N * sizeof(int));

    if(strcmp(caso, "reverse") == 0) {

        for(int i = N; i > 0; i--) {
            sequencia[N - i] = i; 
        }

    } else if(strcmp(caso, "random") == 0) {

        int seed = 12345;
        for(int i = 0; i < N; i++) {
            sequencia[i] = get_random(&seed, N);
        }

    } else if(strcmp(caso, "sorted") == 0) {

        for(int i = 1; i <= N; i++) {
            sequencia[i - 1] = i;
        }
    }    

    if(metodo == 1) {
        quick_sort(sequencia, 0, N - 1);
    } else if(metodo == 2) {
        merge_sort(sequencia, 0, N - 1);
    } else if(metodo == 3) {
        counting_sort(sequencia, N);
    }

    init_crc32();
    uint32_t saida = crc32(0, sequencia, N * sizeof(int));
    printf("%08X", saida);

    //impressão usada para debug
    // printf("\n");
    // for(int i = 0; i < N; i++) {
    //     printf("%d ", sequencia[i]);
    // }

    free(sequencia);

    return 0;
}