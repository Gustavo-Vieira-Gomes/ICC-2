#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPalindromo(char **palavra) {
    // Recebe um ponteiro para um ponteiro de char, e percorre-o comparando o primeiro e o último caractere, se aproximando do centro de ambos os lados
    int start = 0;
    int end = strlen(*palavra) - 1;

    while (start < end) {
        if ((*palavra)[start] == (*palavra)[end]) {
            start++;
            end--;
        } else {
            return false;
        }
    }
    return true;
}

void removeNonAlphaNumeric(char **palavra) {
    // Recebe um ponteiro para um ponteiro de char, e percorre-o removendo caracteres não alfanuméricos
    int i = 0;
    int j = 0;
    while ((*palavra)[i] != '\0') {
        if (isalnum((*palavra)[i])) {
            (*palavra)[j++] = (*palavra)[i];
        }
        i++;
    }
    (*palavra)[j] = '\0';
}

void toUpper(char **palavra) {
    // Recebe um ponteiro para um ponteiro de char, e percorre-o convertendo caracteres minúsculos para maiúsculos
    int i = 0;
    while ((*palavra)[i] != '\0') {
        if ((*palavra)[i] >= 'a' && (*palavra)[i] <= 'z') {
            (*palavra)[i] = (*palavra)[i] - 'a' + 'A';
        }
        i++;
    }
}


int main() {
    char *palavra;
    palavra = (char *)malloc(1000 * sizeof(char));

    // Lê uma linha de qualquer tamanho (sem o '\n'). Retorna NULL no EOF sem dados.
    while (fgets(palavra, 999, stdin) != NULL) {
        // Remove caracteres não alfanuméricos
        removeNonAlphaNumeric(&palavra);
        // Converte caracteres minúsculos para maiúsculos
        toUpper(&palavra);
        // Verifica se a palavra é um palíndromo
        if (isPalindromo(&palavra)) {
            printf("Sim\n");
        } else {
            printf("Não\n");
        }   
    }
}