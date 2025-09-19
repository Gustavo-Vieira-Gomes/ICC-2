// 16907251 - Gustavo Vieira Gomes
// 14558061 - André Campanholo Paschoalini

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//função para imprimir usp formatado
void imprimir_usp(int usp[], int len_usp, int n_comp_usp, int n_trocas_usp) {
    printf("USP - [");
    for(int i = 0; i < len_usp; i++) {
        printf("%d", usp[i]);
        if(i < len_usp - 1) printf(", ");
    }
    printf("]\n");
    printf("Comparações: %d, Trocas: %d\n\n", n_comp_usp, n_trocas_usp);
}

//função para imprimir externos formatado
void imprimir_externos(int ext[], int len_ext, int n_comp_ext, int n_trocas_ext) {
    printf("Externa - [");
    for(int i = 0; i < len_ext; i++) {
        printf("%d", ext[i]);
        if(i < len_ext - 1) printf(", ");
    }
    printf("]\n");
    printf("Comparações: %d, Trocas: %d\n", n_comp_ext, n_trocas_ext);
}

//função auxiliar que troca dois valores
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//função bubble sort com flag que encerra ordenação caso, em alguma iteração antes do fim, não haja nenhuma troca feita
//indicando que o vetor já está ordenado.
void *bubble_sort(int v[], int n, int *comps, int *trocas) {
    *comps = 0;
    *trocas = 0;

    //flag que delata se alguma troca foi feita ou não
    int trocou;
    for(int i = 0; i < n - 1; i++) {
        trocou = 0;
        for(int j = 0; j < n - i - 1; j++) {
            (*comps)++;
            if(v[j] > v[j + 1]) {
                swap(&v[j], &v[j + 1]);
                (*trocas)++;
                //caso alguma troca seja feita flag 'trocou' delata
                trocou = 1;
            }
        }
        //se nenhuma troca foi feita o vetor já está ordenado e 'trocou' = 0, logo, podemos encerrar o bubble sort
        if(!trocou) {
            break;
        }
    }
}

int main() {
    // Aloca memória para os um vetor de inteiros que corresponderão ao número de caracteres de cada nome em cada lista
    int *usp = (int *)calloc(100, sizeof(int));
    //variável que armazena capacidade máxima do vetor usp...
    //será aumentado caso hajam mais linhas de entrada por meio de realloc
    int usp_tam_max = 100;

    //idem acima
    int *externo = (int *)calloc(100, sizeof(int));
    int ext_tam_max = 100;

    //inicializa contadores para a quantidade de corredores da USP e externos
    int cont_usp = 0, cont_ext = 0;

    //cria uma string para receber os nomes dos participantes da corrida
    char participante[500];

    //leitura das strings até EOF
    while(fgets(participante, 499, stdin) != NULL) {
        //scaneia uma substring nome a partir da string original
        char nome[489];
        sscanf(participante, "%488[^-]", nome);
        
        //conta o comprimento do nome, ignorando espaços
        int len_nome = 0;
        for(int j = 0; nome[j] != '\0'; j++) {
            if(nome[j] != ' ' && nome[j] != '\n') //ignora espaços e quebras de linha
                len_nome++;
        }

        //se identificar que o aluno é da USP, insere na primeira posição livre do array
        //usp[] e incrementa qtd de corredores da USP. Caso contrário, faz o mesmo para externo.
        if(strstr(participante, "usp")) {
            if(cont_usp == usp_tam_max) {
                usp_tam_max *= 2; //dobra a capacidade do vetor usp para receber novas linhas de entrada
                usp = realloc(usp, usp_tam_max * sizeof(int)); //realloc o dobro de memória para o vetor
            }
            usp[cont_usp] = len_nome;
            cont_usp++;
        } else if(strstr(participante, "externa")) {
            if(cont_ext == ext_tam_max) {
                ext_tam_max *= 2; //idem acima
                externo = realloc(externo, ext_tam_max * sizeof(int)); //idem acima
            }
            externo[cont_ext] = len_nome;
            cont_ext++;
        }
     
    }

    //cria variáveis para a qtd de comparações e trocas da usp e externos
    int comps_usp, trocas_usp, comps_ext, trocas_ext;

    //chama a função de bubble sort para o vetor da usp e dos externos
    //passa como parâmetros o vetor, o tamanho do vetor e os endereços dos contadores de comparações e trocas
    //pois estes serão modificados dentro da função
    bubble_sort(usp, cont_usp, &comps_usp, &trocas_usp);
    bubble_sort(externo, cont_ext, &comps_ext, &trocas_ext);

    //imprime conforme formatação exigida
    //não requer que passe os contadores de comparações e trocas por referência pois estes não serão modificados na função
    imprimir_usp(usp, cont_usp, comps_usp, trocas_usp);
    imprimir_externos(externo, cont_ext, comps_ext, trocas_ext);

    //liberação de memória
    free(externo);
    free(usp);
        
    return 0;
}
