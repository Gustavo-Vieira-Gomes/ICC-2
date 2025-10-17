#include <stdio.h>

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

int main() {
    int v[8] = {7, 2, 9, 15, 30, 4 ,10 ,11};

    quick_sort(v, 0, 7);

    for(int i = 0; i < 8; i++) {
        printf("%d ", v[i]);
    }
}