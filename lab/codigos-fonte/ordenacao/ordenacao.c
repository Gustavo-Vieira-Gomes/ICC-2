#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct brinquedo {
    char cor[20];
    float comprimento;
    float gosto;
} BRINQUEDO;

void swap_indice(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//retorna false se brinquedo[indice[i]] <= brinquedo[indice[j]] e true se brinquedo[indice[i]] > brinquedo[indice[j]];
bool a_maior_que_b(BRINQUEDO **brinquedo, int indices[], int i, int j) {
    int compara_strings = strcmp(brinquedo[indices[i]]->cor, brinquedo[indices[j]]->cor);

    if(compara_strings < 0) {
        return false;
    } else if(compara_strings == 0) {
        if(brinquedo[indices[i]]->comprimento < brinquedo[indices[j]]->comprimento) {
            return false;
        } else if(brinquedo[indices[i]]->comprimento == brinquedo[indices[j]]->comprimento) {
            if(brinquedo[indices[i]]->gosto > brinquedo[indices[j]]->gosto) {
                return false;
            } else if(brinquedo[indices[i]]->gosto == brinquedo[indices[j]]->gosto) {
                return false;
            } else {
                return true;
            }
        } else {
            return true;
        }
    } else {
        return true;
    }
}

void bubble_sort(BRINQUEDO **brinquedo, int n, int indices[]) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(strcmp(brinquedo[indices[j]]->cor, brinquedo[indices[j + 1]]->cor) > 0) {

                swap_indice(&indices[j], &indices[j + 1]);

            } else if(strcmp(brinquedo[indices[j]]->cor, brinquedo[indices[j + 1]]->cor) == 0) {

                if(brinquedo[indices[j]]->comprimento > brinquedo[indices[j + 1]]->comprimento) {

                    swap_indice(&indices[j], &indices[j + 1]);

                } else if(brinquedo[indices[j]]->comprimento == brinquedo[indices[j + 1]]->comprimento) {

                    if(brinquedo[indices[j]]->gosto < brinquedo[indices[j + 1]]->gosto) {

                        swap_indice(&indices[j], &indices[j + 1]);
                    }
                }
            }
        }
    }
}

//separação dos deslocamentos em duas etapas para que indices[i] (usado dentro da função de comparação)
//não fosse sobrescrito dentro do primeiro for e, portanto, impedir que a função de comparação acessasse
//um valor errado (algum indice[x] anterior que foi deslocado no for)
void insertion_sort(BRINQUEDO **brinquedos, int n, int indices[]) {
    int i, j, elem;

    for(i = 1; i < n - 1; i++) {
        elem = indices[i];    

        j = i - 1;
        while(j >= 0 && a_maior_que_b(brinquedos, indices, j, i)) {
            j--;
            //j para no indice antes do qual deve haver a inserção
        }

        //k começa do elemento antes de i e vai até o j (1 posição antes da inserção) realizando os deslocamentos
        for(int k = i - 1; k > j; k--) {
            indices[k + 1] = indices[k];
        }
        
        indices[j + 1] = elem;
    }
}

void merge_sort(BRINQUEDO **brinquedo) {

}

void quick_sort(BRINQUEDO **brinquedos, int indices[], int ini, int fim) {
    int i = ini, j = fim, pivo = (ini + fim) /2;

    while(i < j) {
        while(!a_maior_que_b(brinquedos, indices, i, pivo) && i < pivo) {
            i++;
        }
        while(a_maior_que_b(brinquedos, indices, j, pivo) && j > pivo) {
            j--;
        }

        if(i <= j)
            swap_indice(&indices[i++], &indices[j--]);
    }

    if(j > ini) 
        quick_sort(brinquedos, indices, ini, j);
    if(i < fim)
        quick_sort(brinquedos, indices, i, fim);

    return;
}

int main() {
    int numero_brinquedos;
    scanf("%d", &numero_brinquedos);

    int indices[numero_brinquedos + 1];

    BRINQUEDO **brinquedos = (BRINQUEDO **)malloc(numero_brinquedos * sizeof(BRINQUEDO*));

    int i = 0;
    while(i < numero_brinquedos) {
        indices[i] = i;

        brinquedos[i] = (BRINQUEDO *)malloc(sizeof(BRINQUEDO));

        scanf("%s %f %f", brinquedos[i]->cor, &brinquedos[i]->comprimento, &brinquedos[i]->gosto);

        i++;
    }

    int metodo_ordenacao;
    scanf("%d", &metodo_ordenacao);

    switch(metodo_ordenacao) {
        case 1:
            bubble_sort(brinquedos, numero_brinquedos, indices);
            break;
        case 2:
            insertion_sort(brinquedos, numero_brinquedos + 1, indices);
            break;
        case 3:
            merge_sort(brinquedos);
            break;
        case 4:
            quick_sort(brinquedos, indices, 0, numero_brinquedos - 1);
            break;
    }

    for(int x = 0; x < numero_brinquedos; x++) {
        printf("%d;", indices[x]);
    }
    printf("\n");

    for(i = 0; i < numero_brinquedos; i++) {
        free(brinquedos[i]);
    }
    free(brinquedos);

    return 0;
}