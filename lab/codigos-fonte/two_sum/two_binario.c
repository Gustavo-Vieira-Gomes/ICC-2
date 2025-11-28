//André Campanholo Paschoalini - 14558061
//Gustavo Vieira Gomes - 16907251

#include <stdio.h>
#include <stdlib.h>

//Troca dois valores inteiros
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Ordena o vetor para busca binária
void quick_sort(int v[], int ini, int fim) {
    int i = ini, j = fim, pivo = v[(ini + fim) / 2];

    while(i <= j) {
        while(v[i] < pivo) i++;
        while(v[j] > pivo) j--;

        if(i <= j) {
            swap(&v[i], &v[j]);
            i++;
            j--;
        }
    }

    if(ini < j) quick_sort(v, ini, j);
    if(i < fim) quick_sort(v, i, fim);
}

//Busca binária que retorna 1 caso encontre, 0 caso contrário
int busca_binaria(int v[], int ini, int fim, int chave) {
    if(ini > fim) return 0;

    int meio = (ini + fim) / 2;

    if(v[meio] == chave) {
        return 1;
    } else if(v[meio] > chave) {
        return busca_binaria(v, ini, meio - 1, chave);
    } else {
        return busca_binaria(v, meio + 1, fim, chave);
    }
}

int main() {
    int N, M;
    scanf("%d", &N);
    int *array = (int *)malloc(N * sizeof(int));

    for(int i = 0; i < N; i++) {
        scanf("%d", &array[i]);
    }

    //Ordena o vetor
    quick_sort(array, 0, N - 1);

    scanf("%d", &M);

    int procurado;
    for(int i = 0; i < M; i++) {
        scanf("%d", &procurado);

        int encontrou = 0;
        for(int j = 0; j < N - 1; j++) {
            int complemento = procurado - array[j];
            //Verifica se complemento é maior do que maior elemento do vetor, pulando a busca pelo complemento caso seja
            if(complemento > array[N - 1]) continue;

            encontrou = busca_binaria(array, j + 1, N - 1, complemento);
            if(encontrou == 1) break;
        }
        
        (encontrou ? printf("S\n") : printf("N\n"));
    }

    free(array);

    return 0;
}