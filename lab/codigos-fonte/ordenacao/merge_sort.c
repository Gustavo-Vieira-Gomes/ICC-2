#include <stdio.h>

void merge(int v[], int ini, int meio, int fim) {
    int n1, n2;

    n1 = meio - ini + 1;
    n2 = fim - meio;

    int L[n1], R[n2];
    
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
}

void merge_sort(int v[], int ini, int fim) {
    int meio;
    if(ini < fim) {
        meio = (ini + fim) / 2;
        merge_sort(v, ini, meio);
        merge_sort(v, meio + 1, fim);
        merge(v, ini, meio, fim);
    }
}

int main() {
    int v[8] = {7, 2, 9, 15, 30, 4 ,10 ,11};

    merge_sort(v, 0, 7);

    for(int i = 0; i < 8; i++) {
        printf("%d ", v[i]);
    }
}