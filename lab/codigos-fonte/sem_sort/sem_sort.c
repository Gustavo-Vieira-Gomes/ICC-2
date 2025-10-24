//André Campanholo Paschoalini - NºUSP: 14558061
//Gustavo Vieira Gomes - NºUSP: 16907251

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "util.h"

//Função de troca de dois valores
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Função booleana que verifica se o vetor está ordenado ou não
bool ordenada(int v[], int N) {
    for(int i = 0; i < N - 1; i++) {
        if(v[i + 1] < v[i]) return false;
    }
    return true;
}

//Algoritmo de fisher yates que aplica a ordenação aleatória/bogosort
void fisher_yates_shuffle(int v[], int N, int *seed) { //Passagem da seed por referência
    int i, j;

    for(i = N - 1; i > 0; i--) {
        j = get_random(seed, i) - 1; //Gera algum índice aleatório do vetor e que será trocado com o elemento de índice i
        swap(&v[i], &v[j]); //Troca os elementos de lugar
    }
}

int main() {
    int N;
    scanf("%d", &N);

    int *sequencia = (int *)calloc(N, sizeof(int));

    int seed = 12345;
    for(int i = 0; i < N; i++) {
        sequencia[i] = get_random(&seed, N); //Geração da sequência inicial aleatória
    }

    //Laço que, a cada iteração, verifica se o vetor está ordenado: caso não, chama o FisherYates e incrementa o contador de chamadas; caso sim, encerra a repetição
    int cont = 0;
    while(!ordenada(sequencia, N)) {
        fisher_yates_shuffle(sequencia, N, &seed);
        cont++;
    }

    //Impressão conforme formato solicitado
    printf("%d\n", cont);
    for(int i = 0; i < N; i++) {
        printf("%d ", sequencia[i]);
    }
    
    free(sequencia);

    return 0;
}