#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "util.h"

//André Campanholo Paschoalini - NºUSP: 14558061
//Gustavo Vieira Gomes - NºUSP: 16907251


//Função que troca valores inteiros
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Implementação do quick sort
void quick_sort(int v[], int ini, int fim) {
    //pivo determinado como o elemento central do vetor (ideal para caso reverse ou sorted e pode ou não ser uma boa escolha para random)
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

//Implementação da função de intercalação do merge sort 
void merge(int v[], int ini, int meio, int fim) {
    int n1 = meio - ini + 1, n2 = fim - meio;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    
    for(int i = 0; i < n1; i++) {
        L[i] = v[ini + i];
    }

    for(int i = 0; i < n2; i++) {
        R[i] = v[meio + 1 + i];
    }

    int i = 0, j = 0, k = ini;

    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            v[k++] = L[i++];
        } else {
            v[k++] = R[j++];
        }
    }

    while(i < n1) {
        v[k++] = L[i++];
    }
    while(j < n2) {
        v[k++] = R[j++];
    }

    free(L);
    free(R);
}

//Implementação da função de divisão do vetor do merge sort
void merge_sort(int v[], int ini, int fim) {
    if(ini < fim) {
        int meio = ini + (fim - ini) / 2;
        merge_sort(v, ini, meio);
        merge_sort(v, meio + 1, fim);
        merge(v, ini, meio, fim);
    }
}
//Merge Sort não utilizado devido à necessidade de memória auxiliar, a qual é limitada pelo cenário do exercício

/*Implementação do insertion sort
(Não viável individualmente para o exercício devido a sua alta complexidade temporal/ineficiência para N grande)*/
void insertion_sort(int v[], int n) {
    int i, j, elem;

    for(i = 1; i < n; i++) {
        elem = v[i];

        for(j = i - 1; j >= 0 && elem < v[j]; j--) {
            v[j + 1] = v[j];
        }

        v[j + 1] = elem;
    }
}

//Implementação do shell sort (seleção dos valores dos incrementos na main)
void shell_sort(int v[], int n, int incrementos[], int shells) {
    int inc_atual, i, j, h, elem;

    for(inc_atual = 0; inc_atual < shells; inc_atual++) {
        h = incrementos[inc_atual];

        for(i = h; i < n; i++) {
            elem = v[i];

            for(j = i - h; j >= 0 && v[j] > elem; j -= h)
                v[j + h] = v[j];

            v[j + h] = elem;
        }
    }
}

/*Implementação do counting sort
(Não utilizado pois utiliza memória auxiliar, inviável para o exercício apesar da complexidade O(n))*/
void counting_sort(int v[], int n) {
    int min = v[0], max = v[0];

    for(int i = 1; i < n; i++) {
        if(v[i] < min) min = v[i];
        if(v[i] > max) max = v[i];
    }

    int ajuste = max - min + 1;

    int *aux = (int *)calloc(ajuste, sizeof(int));

    for(int i = 0; i < n; i++) {
        aux[v[i] - min]++;
    }

    int j = 0;
    for(int i = 0; i < ajuste; i++) {
        while(aux[i] != 0) {
            v[j++] = i + min;
            aux[i]--;
        }
    }

    free(aux);
}

//Implementação da função de construção da heap máxima
void heapify(int v[], int n, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if(esq < n && v[esq] > v[maior])
        maior = esq;

    if(dir < n && v[dir] > v[maior])
        maior = dir;

    if(maior != i) {
        swap(&v[i], &v[maior]);
        heapify(v, n, maior);
    }
}

//Implementação do heap sort
void heap_sort(int v[], int n) {
    for(int i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);

    for(int i = n - 1; i > 0; i--) {
        swap(&v[0], &v[i]);
        heapify(v, i, 0);
    }
}
//Heap sort por si só não viável pois excede o tempo de execução 

//Implementação do introSort (usa pontos fortes de 3 algoritmos de ordenação diferentes)
void intro_sort(int v[], int ini, int fim, int profundidade) {
    if(fim - ini + 1 < 16) {
        //Insertion sort quando faltam apenas 16 elementos a serem ordenados pois o insertion é eficiente para n pequeno
        insertion_sort(v + ini, fim - ini + 1); 

    } else if(profundidade == 0) {
        //Quando a profundidade excede o limite (log(N) * 2) interrompe a recursão do quick sort e chama o heap sort para não estourar a memória da stack
        heap_sort(v + ini, fim - ini + 1);

    } else {
        //Enquanto nenhuma das condições acima é comprida funciona como um quick sort comum
        int i = ini, j = fim, pivo = v[ini + (fim - ini) / 2];

        while(i <= j) {
            while(v[i] < pivo) i++;
            while(v[j] > pivo) j--;

            if(i <= j) {
                swap(&v[i], &v[j]);
                i++;
                j--;
            }
        }

        //A cada chamada reduz em 1 a profundidade para (começa em log(N) * 2 e vai até zero, logo, profundidade limite = log(N) * 2)
        if(ini < j) intro_sort(v, ini, j, profundidade - 1);
        if(i < fim) intro_sort(v, i, fim, profundidade - 1);
    }

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
        int incrementos[20], temp[20];
        int shells = 0;
        
        //Incrementos de 3*h + 1 (1, 4, 13, 40, 121...)
        for(int h = 1; h < N && shells < 20; h = 3 * h + 1) {
            temp[shells] = h;
            incrementos[shells++] = h;
        }

        //Inverte o vetor de incrementos pois os incrementos devem ter ordem decrescente e o último incremento deve ser de 1 em 1
        for(int i = 0; i < 20; i++) {
            incrementos[i] = temp[shells - 1 - i];
        }
        
        shell_sort(sequencia, N, incrementos, shells);

    } else if(metodo == 3) {
        //Determina profundida limite como log(N) * 2
        int prof_limite = log2(N) * 2;
        intro_sort(sequencia, 0, N - 1, prof_limite);

    }

    //Hashing da saída
    init_crc32();
    uint32_t saida = crc32(0, sequencia, N * sizeof(int));
    printf("%08X", saida);

    //Impressão usada para debug
    // printf("\n");
    // for(int i = 0; i < N; i++) {
    //     printf("%d ", sequencia[i]);
    // }

    free(sequencia);

    return 0;
}