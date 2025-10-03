//André Campanholo Paschoalini - NºUSP: 14558061
//Gustavo Vieira Gomes - NºUSP: 16907251

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//struct brinquedo que contem cada campo usado na comparação dos brinquedos
typedef struct brinquedo {
    char cor[20];
    float comprimento;
    float gosto;
} BRINQUEDO;

//função que swapa ordenação dos índices do brinquedos
void swap_indice(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//retorna false se brinquedos estão na ordem correta e true se é necessário swapá-los.
bool a_maior_que_b(BRINQUEDO **brinquedo, int indices[], int i, int j) {
    int indice_i = indices[i];
    int indice_j = indices[j];
    
    //comparação da ordem alfabética da cor dos brinquedos
    int compara_strings = strcmp(brinquedo[indice_i]->cor, brinquedo[indice_j]->cor);

    if(compara_strings < 0) {
        return false;
    } else if(compara_strings == 0) {
        //comparação dos comprimentos dos brinquedos
        if(brinquedo[indice_i]->comprimento < brinquedo[indice_j]->comprimento) {
            return false;
        } else if(brinquedo[indice_i]->comprimento == brinquedo[indice_j]->comprimento) {
            //comparação da nota dos brinquedos
            if(brinquedo[indice_i]->gosto > brinquedo[indice_j]->gosto) {
                return false;
            } else if(brinquedo[indice_i]->gosto == brinquedo[indice_j]->gosto) {
                //comparação do índice dos brinquedos para garantir que a ordenação é estável
                if (indice_i > indice_j) {
                    return true;
                } else {
                    return false;
                }
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

//ordena comparando elementos adjcentes e swapando seus índices
void bubble_sort(BRINQUEDO **brinquedo, int n, int indices[]) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(a_maior_que_b(brinquedo, indices, j, j + 1)) {
                swap_indice(&indices[j], &indices[j + 1]);
            }
        }
    }
}

//percorre o vetor do elemento chave para trás até achar um menor e o insere na posição seguinte
void insertion_sort(BRINQUEDO **brinquedos, int n, int indices[]) {
    int i, j, elem;

    for(i = 1; i < n; i++) {
        //seleção do elemento chave
        elem = indices[i];    

        j = i - 1;
        while(j >= 0) {
            //como a função desloca os elementos do vetor de indices, a cada repetição é possível que o indice i seja sobrescrito, assim perdemo o índice original...
            //para combater isso, criamos um vetor de indices auxiliar que guarda o elem/chave. Assim, não perdemos o índice que está sendo ordenado e podemos inseri-lo
            //após o break
            int indices_aux[2];
            indices_aux[0] = indices[j];
            indices_aux[1] = elem;

            //enquanto o brinquedo[j] > brinquedo[elem/chave] desloca os indices para frente.. quando encontra um brinquedo menor sai do laço e insere na posição seguinte
            if(a_maior_que_b(brinquedos, indices_aux, 0, 1)) {
                indices[j + 1] = indices[j];
                j--;
            } else {
                break;
            }
        }

        //inserção da chave na posição correta
        indices[j + 1] = elem;
    }
}

//intercala os vetores unitários provenientes da função merge_sort ordenando-os (etapa de conquista)
void merge(BRINQUEDO **brinquedos, int indices[], int ini, int meio, int fim) {
    int i, j, k, n1, n2;

    //comprimento dos vetores auxiliares esquerda e direita
    n1 = meio - ini + 1;
    n2 = fim - meio;

    //aloca memória para os vetores esquerda e direita dinamicamente devido ao altíssimo número de brinquedos (evita stack overflow)
    int *indices_L = (int *)malloc(n1 * sizeof(int));
    int *indices_R = (int *)malloc(n2 * sizeof(int));

    //inicializa os dois vetores com os elementos a esquerda e a direita do vetor original de indices  
    for(i = 0; i < n1; i++)
        indices_L[i] = indices[ini + i];
    for(j = 0; j < n2; j++)
        indices_R[j] = indices[meio + 1 + j];

    i = j = 0;

    //ordena o vetor original de indices selecionando primeiro os menores do vetor da esquerda ou direita
    for(k = ini; k <= fim; k++) {
        //ifs não permitem acesso a indices inválidos... caso uma das metades (vetores esq/L e dir/R) ja tenha sido esvaziada, completa o restante do
        //vetor original de índices com os elementos que sobraram do vetor da outra metade (a cada merge a metade é ordenada, logo é garantido que
        //os elementos que sobraram podem ser inseridos sem ter que ordená-los)
        if(i >= n1) {
            indices[k] = indices_R[j];
            j++;
        } else if(j >= n2) {
            indices[k] = indices_L[i];
            i++;
        } else {
            //como o vetor original de índices é modificado a cada iteração é preciso criar um vetor auxiliar de índices para não perder um índice que foi sobrescrito
            int indices_aux[2];
            indices_aux[0] = indices_L[i];
            indices_aux[1] = indices_R[j];

            //antes de qualquer metade ser esvaziada ordena o vetor original comparando os elementos do vetor de indices_L e indices_R
            if(!a_maior_que_b(brinquedos, indices_aux, 0, 1)) {
                indices[k] = indices_L[i];
                i++;
            } else {
                indices[k] = indices_R[j];
                j++;
            }
        }
    }
    
    free(indices_L);
    free(indices_R);
}

//função que divide o vetor orignal até que existam apenas vetores unitátios (etapa de divisão) e chama a função que os intercala
void merge_sort(BRINQUEDO **brinquedos, int indices[], int ini, int fim) {
    int meio = (ini + fim) / 2;
    if(ini < fim) {
        merge_sort(brinquedos, indices, ini, meio);
        merge_sort(brinquedos, indices, meio + 1, fim);
        merge(brinquedos, indices, ini, meio, fim);
    }
}

//seleciona um pivo e e garante que todos os elementos antes do pivo são menores, e os que estão depois são todos maiores
void quick_sort(BRINQUEDO **brinquedos, int indices[], int ini, int fim) {
    //caso base/proibido
    if (ini >= fim) return;
    
    //inicializa o pivo como o valor da posição inicial do vetor de indices
    int pivo = indices[ini];
    
    //inicializa i na posição inicial, junto com o pivo
    int i = ini;
    int j;

    //inicializa j como i + 1 e incrementa-o até o último elemento
    for(j = ini + 1; j <= fim; j++) {
        //é possível que haja um swap do pivo com outro elemento, e nesse caso o pivo original é sobrescrito
        int indices_aux[2];
        indices_aux[0] = indices[j];
        indices_aux[1] = pivo;

        //se o brinquedo j for menor que o pivo swapa o elemento a frente do pivo (ou qualquer outro a frente do pivo, 
        //a depender de quantas iterações já se passara) com o j
        if(!a_maior_que_b(brinquedos, indices_aux, 0, 1)) {
            i++;
            swap_indice(&indices[i], &indices[j]);
        }
    }

    //swapa o pivo com a posição em que o i terminou, que se trata da posição em que todos os elemento anteriores são menores e os próximos são maiores
    swap_indice(&indices[ini], &indices[i]);

    //chamada recursiva
    quick_sort(brinquedos, indices, ini, i - 1);
    quick_sort(brinquedos, indices, i + 1, fim);
}

int main() {
    int numero_brinquedos;
    scanf("%d", &numero_brinquedos);

    //criação do vetor de índices dos brinquedos
    int indices[numero_brinquedos + 1];

    //alocação dinâmica de memória para um vetor de ponteiros para brinquedos
    BRINQUEDO **brinquedos = (BRINQUEDO **)malloc(numero_brinquedos * sizeof(BRINQUEDO*));

    int i = 0;
    while(i < numero_brinquedos) {
        indices[i] = i;

        //alocação de memória para os ponteiros para brinquedo (cada brinquedo, portanto, é tratado como um ponteiro para a struct brinquedo)
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
            merge_sort(brinquedos, indices, 0, numero_brinquedos - 1);
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