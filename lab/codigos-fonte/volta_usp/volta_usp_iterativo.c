// 16907251 - Gustavo Vieira Gomes
// 14558061 - André Campanholo Paschoalini

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Aloca memória para um vetor de strings
    char **participantes = (char **)malloc(100 * sizeof(char *));
    for(int i = 0; i < 100; i++) {
        participantes[i] = (char *)malloc(50 * sizeof(char));
    }

    // Aloca memória para os inteiros que corresponderão ao número de caracteres de cada nome em cada lista
    int *usp = (int *)calloc(100, sizeof(int));
    int *externo = (int *)calloc(100, sizeof(int));

    // Inicializa contadores para a quantidade de corredores da USP e externos
    int i = 0, cont_usp = 0, cont_ext = 0;
    
    // Leitura das strings até EOF
    while(fgets(participantes[i], 49, stdin) != NULL) {
        // Scaneia uma substring nome a partir da string original
        char nome[35];
        sscanf(participantes[i], "%34[^-]", nome);
        
        // Conta o comprimento do nome, ignorando espaços
        int len_nome = 0;
        for(int j = 0; nome[j] != '\0'; j++) {
            if(nome[j] != ' ' && nome[j] != '\n') // Ignora espaços e quebras de linha
                len_nome++;
        }

        // Se identificar que o aluno é da USP, insere na primeira posição livre do array
        // usp[] e incrementa qtd de corredores da USP. Caso contrário, faz o mesmo para externo.
        if(strstr(participantes[i], "usp")) {
            usp[cont_usp] = len_nome;
            cont_usp++;
        } else if(strstr(participantes[i], "externa")) {
            externo[cont_ext] = len_nome;
            cont_ext++;
        }

        i++;
    }

    //impressão
    printf("USP - [");
    for(int i = 0; i < cont_usp; i++) {
        printf("%d", usp[i]);
        if(i < cont_usp - 1) printf(", ");
    }
    printf("]\n");
    printf("Externa - [");
    for(int i = 0; i < cont_ext; i++) {
        printf("%d", externo[i]);
        if(i < cont_ext - 1) printf(", ");
    }
    printf("]\n");

    //liberação de memória
    free(externo);
    free(usp);
    for(int i = 0; i < 100; i++) {
        free(participantes[i]);
    }
    free(participantes);
    
    return 0;
}
