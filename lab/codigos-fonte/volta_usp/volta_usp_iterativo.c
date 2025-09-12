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

    int i = 0, cont_usp = 0, cont_ext = 0;
    while(fgets(participantes[i], 49, stdin) != NULL) {
        remove_spaces(participantes[i], strlen(participantes[i]));

        char nome[35];
        sscanf(participantes[i], "%[^-]", nome);

        if(strstr(participantes[i], "usp")) {
            usp[cont_usp] = strlen(nome);
            cont_usp++;
        } else {
            externo[cont_ext] = strlen(nome);
            cont_ext++;
        }

        i++;
    }

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

    free(externo);
    free(usp);
    for(int i = 0; i < 100; i++) {
        free(participantes[i]);
    }
    free(participantes);
    
    return 0;
}