// 16907251 - Gustavo Vieira Gomes
// 14558061 - André Campanholo Paschoalini

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//remove todos os espaços de cada linha
void remove_spaces(char v[], int len) {
    int j = 0;
    for(int i = 0; i < len; i++) {
        if (v[i] != ' ') {
            v[j++] = v[i];
        }
    }
    v[j] = '\0';
}

int main() {
    //aloca memória para um vetor de strings
    char **participantes = (char **)malloc(100 * sizeof(char *));
    for(int i = 0; i < 100; i++) {
        participantes[i] = (char *)malloc(50 * sizeof(char));
    }

    //aloca memória para os inteiros que corresponderão ao número de caracteres de cada nome em cada lista
    int *usp, *externo;
    usp = (int *)calloc(100, sizeof(int));
    externo = (int *)calloc(100, sizeof(int));

	//inicializa contadores para a quantidade de corredores da usp
	//e a quantidade de corredores externos
    int i = 0, cont_usp = 0, cont_ext = 0;
    
    //Leitura das strings até EOF
    while(fgets(participantes[i], 49, stdin) != NULL) {
		//remoção dos espaços
        remove_spaces(participantes[i], strlen(participantes[i]));
        
		//scaneia uma substring nome a partir da string original
        char nome[35];
        sscanf(participantes[i], "%[^-]", nome);
        
        //conta o comprimento do nome
        int len_nome = 0;
	      for(int i = 0; nome[i] != '\0'; i++) {
				     len_nome++;
	      }

		//se identificar que o aluno é da usp, insere na primeira posição livre do array
		//usp[] e incrementa qtd de corredores da usp. Caso contrário, faz o contrário.
        if(strstr(participantes[i], "usp")) {
            usp[cont_usp] = len_nome;
            cont_usp++;
        } else {
            externo[cont_ext] = len_nome;
            cont_ext++;
        }

        i++;
    }

	//imprime segundo template exigido
    printf("USP - [");
    for(int i = 0; i < cont_usp; i++) {
        if(i < cont_usp - 1) {
            printf("%d, ", usp[i]);
        } else {
            printf("%d]\n", usp[i]);
        }
    }

    printf("Externa - [");
    for(int i = 0; i < cont_ext; i++) {
        if(i < cont_ext - 1) {
            printf("%d, ", externo[i]);
        } else {
            printf("%d]\n", externo[i]);
        }
    }

	//liberação de memória
    free(externo);
    free(usp);
    for(int i = 0; i < 100; i++) {
        free(participantes[i]);
    }
    free(participantes);
    
    return 0;
}