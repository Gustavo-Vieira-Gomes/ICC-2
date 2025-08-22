//André Campanholo Paschoalini - NºUSP: 14558061
//Gustavo Vieira Gomes - NºUSP: 16907251

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool palindromo(char v[], int n) {
    //recebe um vetor de caracteres e o seu comprimento, comparando sempre o primeiro e o último caractere: caso seja diferentes, 
    //retorna 'false', caso não, compara o segundo e o penúltimo caractere, e assim por diante até todos serem comparados. Sendo um palindromo, retorna 'true'.
    if(v[0] != v[n - 1]) {
        return false;
    } else if(n <= 1) {
        return true;
    } else {
        return palindromo(v + 1, n - 2);
    }
};

void removeNonAlphaNumeric(char **palavra) {
    //recebe um ponteiro de ponteiro para char e retira caracteres não alphanuméricos.
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
    //recebe um ponteiro de ponteiro para char e transforma todos os caracteres em maiúsculos
    int i = 0;
    while ((*palavra)[i] != '\0') {
        if ((*palavra)[i] >= 'a' && (*palavra)[i] <= 'z') {
            (*palavra)[i] = (*palavra)[i] - 'a' + 'A';
        }
        i++;
    }
}

int main() {
    //declara da string por meio de ponteiro e alocação dinâmica de memória.
    char *palavra;
    palavra = (char *)malloc(100 * sizeof(char));

    //leitura das strings por linha até EOF
    while(fgets(palavra, 99, stdin) != NULL) {
        //chama função que remove caracteres não alphanuméricos.
        removeNonAlphaNumeric(&palavra);

        //chama função que transforma caracteres em maiúsculo.
        toUpper(&palavra);

        //caso a string seja uma palavra, imprime "Sim", caso contrário, imprime "Não".
        if(palindromo(palavra, strlen(palavra)) || strlen(palavra) == 0) {
            printf("Sim\n");
        } else {
            printf("Não\n");
        }
    }
    
    return 0;
}

