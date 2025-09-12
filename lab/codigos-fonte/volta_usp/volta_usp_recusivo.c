// 16907251 - Gustavo Vieira Gomes
// 14558061 - André Campanholo Paschoalini

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Função recursiva para contar o número de letras sem espaços
int count_letters_without_spaces(char *str) {
    if (str[0] == '-') return 0;
    if (str[0] == ' ') return count_letters_without_spaces(str + 1);
    return 1 + count_letters_without_spaces(str + 1);
}

// Função principal
int main() {
    char *line = (char *)malloc(100 * sizeof(char));
    int *usp_values = (int *)malloc(1*sizeof(int)), *external_values = (int *)malloc(1*sizeof(int)), usp_count = 0, external_count = 0;

    // Lê as linhas de entrada
    while (fgets(line, 100, stdin) != NULL) {

        // Verifica se a linha é de pessoa externa
        if (strstr(strchr(line, '-') + 2, "externa") != NULL) {
            // Se for a primeira pessoa externa, aloca o valor na primeira posição do vetor
            if (external_count == 0) {
                external_values[external_count] = count_letters_without_spaces(line);
            } else {
                // Se não for a primeira pessoa externa, realoca o tamanho do vetor e insere o valor na última posição
                external_values = (int *)realloc(external_values, (external_count + 1) * sizeof(int));
                external_values[external_count] = count_letters_without_spaces(line);
            }
            external_count++;
        // Verifica se a linha é de pessoa USP
        } else if (strstr(strchr(line, '-') + 2, "usp") != NULL) {
            // Se for a primeira pessoa USP, aloca o valor na primeira posição do vetor
            if (usp_count == 0) {
                usp_values[usp_count] = count_letters_without_spaces(line);
            } else {
                // Se não for a primeira pessoa USP, realoca o tamanho do vetor e insere o valor na última posição
                usp_values = (int *)realloc(usp_values, (usp_count + 1) * sizeof(int));
                usp_values[usp_count] = count_letters_without_spaces(line);
            }
            usp_count++;
        }
    }

    printf("USP - [");
    // Imprime o vetor de valores de USP
    for(int i = 0; i < usp_count; i++) {
        if(i < usp_count - 1) {
            printf("%d, ", usp_values[i]);
        } else {
            printf("%d]\n", usp_values[i]);
        }
    }

    printf("Externa - [");
    // Imprime o vetor de valores de externa
    for(int i = 0; i < external_count; i++) {
        if(i < external_count - 1) {
            printf("%d, ", external_values[i]);
        } else {
            printf("%d]\n", external_values[i]);
        }
    }

    // Libera a memória alocada para os vetores
    free(usp_values);
    free(external_values);
    free(line);

    return 0;
}