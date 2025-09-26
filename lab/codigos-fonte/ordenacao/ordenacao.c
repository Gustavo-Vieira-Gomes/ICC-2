#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void insertion_sort(BRINQUEDO **brinquedo, int n, int indices[]) {
    int i, j, swapar;
    for(i = 1; i < n; i++) {

        j = i - 1;

        while(j >= 0) {
            

            j--;
        }

    }
}

void merge_sort(BRINQUEDO **brinquedo) {

}

void quick_sort(BRINQUEDO **brinquedo) {

}

int main() {
    int numero_brinquedos;
    scanf("%d", &numero_brinquedos);

    int indices[numero_brinquedos];

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
            insertion_sort(brinquedos, numero_brinquedos, indices);
            break;
        case 3:
            merge_sort(brinquedos);
            break;
        case 4:
            quick_sort(brinquedos);
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