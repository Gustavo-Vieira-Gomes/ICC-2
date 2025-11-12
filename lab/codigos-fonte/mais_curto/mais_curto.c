//André Campanholo Paschoalini - 14558061
//Gustavo Vieira Gomes - 16907251

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Struct das datas
typedef struct data DATA;
struct data {
    int dia;
    int mes;
    int ano;
};

//Definição das structs para lista encadeada (hashing aberto)
typedef struct no {
    struct no *proximo;
    DATA *data;
} NO;

typedef struct lista {
    NO *inicio;
    NO *fim;
    int tamanho;
} LISTA;

//Hashing Aberto: Implementação de lista encadeada

//Cria uma lista simplesmente encadeada
LISTA *lista_criar(void) {
    LISTA *l = (LISTA *)malloc(sizeof(LISTA));
    if(l != NULL) {
        l->inicio = NULL;
        l->fim = NULL;
        l->tamanho = 0;
    }
    return l;
}   

//Verifica se lista está vazia
bool lista_vazia(LISTA *l) {
    if(l != NULL && l->tamanho == 0) return true;
    return false;
}

//Insere uma data na lista
bool lista_inserir(LISTA *l, DATA *data_q) {
    if(l == NULL || data_q == NULL) return false;

    NO *novo = (NO *)malloc(sizeof(NO));
    if(novo != NULL) {
        novo->data = data_q;
        novo->proximo = NULL;

        if(lista_vazia(l)) {
            l->inicio = novo;
        } else {
            l->fim->proximo = novo;
        }
        
        l->fim = novo;
        l->tamanho++;

        return true;
    }
    return false;
}

//Função de swap de duas datas
void swap_datas(DATA *a, DATA *b) {
    DATA temp = *a;
    *a = *b;
    *b = temp;
}

//Ordena as datas de acordo com o ano
void quick_sort_anos(DATA v[], int ini, int fim) {
    int i = ini, j = fim, pivo = v[(fim + ini) / 2].ano;

    while(i <= j) {
        while(v[i].ano < pivo) i++;
        while(v[j].ano > pivo) j--;

        if(i <= j) {
            swap_datas(&v[i], &v[j]);
            i++;
            j--;
        }
    }

    if(ini < j) quick_sort_anos(v, ini, j);
    if(i < fim) quick_sort_anos(v, i, fim);
}

//Ordena as datas de acordo com o mês
void quick_sort_meses(DATA v[], int ini, int fim) {
    int i = ini, j = fim, pivo = v[(fim + ini) / 2].mes;

    while(i <= j) {
        while(v[i].mes < pivo) i++;
        while(v[j].mes > pivo) j--;

        if(i <= j) {
            swap_datas(&v[i], &v[j]);
            i++;
            j--;
        }
    }

    if(ini < j) quick_sort_meses(v, ini, j);
    if(i < fim) quick_sort_meses(v, i, fim);
}

//Ordena as datas de acordo com os dias
void quick_sort_dias(DATA v[], int ini, int fim) {
    int i = ini, j = fim, pivo = v[(fim + ini) / 2].dia;

    while(i <= j) {
        while(v[i].dia < pivo) i++;
        while(v[j].dia > pivo) j--;

        if(i <= j) {
            swap_datas(&v[i], &v[j]);
            i++;
            j--;
        }
    }

    if(ini < j) quick_sort_dias(v, ini, j);
    if(i < fim) quick_sort_dias(v, i, fim);
}

//Função de ordenação das datas hierarquicamente
void ordenar_datas(DATA *datas_n, int n) {
    //Ordena os anos
    quick_sort_anos(datas_n, 0, n - 1);
    
    int i = 0; 
    while(i < n) {
        int ano = datas_n[i].ano, j = i + 1;
        while(j < n && datas_n[j].ano == ano) {
            j++;
        }
        if(j != i + 1) {
            //Caso existem várias datas com o mesmo ano, ordena-as pelo mês
            quick_sort_meses(datas_n, i, j - 1);

            int k = i;
            while(k < j) {
                int mes = datas_n[k].mes, h = k + 1;
                while(h < j && datas_n[h].mes == mes) {
                    h++;
                }
                if(h != k + 1) {
                    //caso existam várias datas com o mesmo mês e ano, ordena-as pelo dia
                    quick_sort_dias(datas_n, k, h - 1);
                }
                k = h;
            }
        }
        i = j;
    }
}

//Realiza a busca binária de uma data entre as N datas
bool busca_binaria(DATA *datas_n, int ini, int fim, DATA data_q) {
    if(ini > fim) return false;
    
    int meio = (fim + ini) / 2;

    if(data_q.ano == datas_n[meio].ano &&
        data_q.mes == datas_n[meio].mes &&
        data_q.dia == datas_n[meio].dia) {

        return true;

    } else if((data_q.ano < datas_n[meio].ano) ||
        ((data_q.ano == datas_n[meio].ano) && (data_q.mes < datas_n[meio].mes)) ||
        ((data_q.ano == datas_n[meio].ano) && (data_q.mes == datas_n[meio].mes) && (data_q.dia < datas_n[meio].dia))) {

        return busca_binaria(datas_n, ini, meio - 1, data_q);

    } else if((data_q.ano > datas_n[meio].ano) ||
        ((data_q.ano == datas_n[meio].ano) && (data_q.mes > datas_n[meio].mes)) ||
        ((data_q.ano == datas_n[meio].ano) && (data_q.mes == datas_n[meio].mes) && (data_q.dia > datas_n[meio].dia))) {

        return busca_binaria(datas_n, meio + 1, fim, data_q);
    }

    return false;
}

//Hashing fechado implementado porém não utilizado por exceder tempo de execução
// DATA **criar_tabela_hash_datas(DATA *datas_n, int n) {
//     DATA **tabela_hash = (DATA **)malloc(5 * n * sizeof(DATA *));
//     for(int i = 0; i < 5 * n; i++) {
//         tabela_hash[i] = NULL;
//     }

//     //Função de Hashing: h(k) = Sk % n, onde Sk é a soma do dia, do mes e do ano de k;
//     for(int i = 0; i < n; i++) {
//         int indice = (datas_n[i].dia + datas_n[i].mes + datas_n[i].ano) % (5 * n);

//         if(tabela_hash[indice] == NULL) {
//             tabela_hash[indice] = &(datas_n[i]);

//         } else {
//             //Função de ReHashing (Sondagem Linear): Soma incrementa o indice em 1 enquanto não encontrar um bucket vazio;
//             while(tabela_hash[indice] != NULL) {
//                 indice = (indice + 1) % (5 * n);
//             }

//             tabela_hash[indice] = &(datas_n[i]);
//         }
//     }

//     return tabela_hash;
// }

// bool busca_hashing(DATA *datas_n, DATA data_q, DATA **tabela_hash, int n) {
//     int indice_q = (data_q.dia + data_q.mes + data_q.ano) % (5 * n);
//     int indice_original = indice_q;
    
//     do {
//         if(tabela_hash[indice_q] == NULL) {
//             return false;
//         }
        
//         if(tabela_hash[indice_q]->ano == data_q.ano && 
//            tabela_hash[indice_q]->mes == data_q.mes && 
//            tabela_hash[indice_q]->dia == data_q.dia) {
//             return true;
//         }
        
//         indice_q = (indice_q + 1) % (5 * n);

//     } while(indice_q != indice_original);
    
//     return false;
// }

//Cria tabela de hashing para as N datas
LISTA  **criar_hash_table(DATA *datas_n, int n) {
    LISTA **hash_table = (LISTA **)malloc(2 * n * sizeof(LISTA *));
    for(int i = 0; i < 2 * n; i++) {
        hash_table[i] = NULL;
    }

    for(int i = 0; i < n; i++) {
        int indice = (datas_n[i].dia + datas_n[i].mes + datas_n[i].ano) % (2 * n); 
        if(hash_table[indice] == NULL) {
            hash_table[indice] = lista_criar();
        }
        lista_inserir(hash_table[indice], &datas_n[i]);
    }

    return hash_table;
}

//Realiza a busca das Q datas na tabela de hashing (percorre lista encadeada para casos de colisão)
bool busca_hash(DATA data_q, LISTA **hash_table, int n) {
    int indice = (data_q.dia + data_q.mes + data_q.ano) % (2 * n);

    if(hash_table[indice] == NULL) return false;

    NO *aux = hash_table[indice]->inicio;
    while(aux != NULL) {
        if(aux->data->dia == data_q.dia &&
           aux->data->mes == data_q.mes &&
           aux->data->ano == data_q.ano) 
            return true;
        aux = aux->proximo;
    }

    return false;
}

//Realiza a busca sequencial de uma data entre as N datas 
bool busca_sequencial(DATA *datas_n, DATA data_q, int n) {
    for(int i = 0; i < n; i++) {
        if(data_q.ano == datas_n[i].ano && data_q.mes == datas_n[i].mes && data_q.dia == datas_n[i].dia) {
            return true;
        }
    }
    return false;
}

//Função de seleção do método de busca
bool buscar_data(DATA *datas_n, DATA data_q, int n, int metodo, LISTA **tabela_hash) {
    switch(metodo) {
        case 1:
            return busca_binaria(datas_n, 0, n - 1, data_q);
            break;

        case 2:
            return busca_hash(data_q, tabela_hash, n);
            break;

        case 3:
            return busca_sequencial(datas_n, data_q, n);
            break;
            
        default:
            return false;
            break;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    //Vetor das N datas
    DATA *datas_n = (DATA *)malloc(n * sizeof(DATA));

    int i = 0;
    while(i < n) {
        //Leitura das N datas no formato pré-determinado (dia, mes e ano são inteiros)
        scanf("%d-%d-%d", &datas_n[i].dia, &datas_n[i].mes, &datas_n[i].ano);
        i++;
    }

    int q;
    scanf("%d", &q);
    //Vetor das Q datas
    DATA *datas_q = (DATA *)malloc(q * sizeof(DATA));

    i = 0;
    while(i < q) {
        //Leitura das Q datas
        scanf("%d-%d-%d", &datas_q[i].dia, &datas_q[i].mes, &datas_q[i].ano);
        i++;
    }

    int metodo;
    scanf("%d", &metodo);

    //Cria um vetor de ponteiros para lista para servir de tabela de hashing (inicializada com NULL caso não seja utilizada)
    LISTA **tabela_hash = NULL;

    if(metodo == 1) {
        //Caso queira fazer busca binária, ordena as datas
        ordenar_datas(datas_n, n);
    } else if(metodo == 2) {
        //Caso queira fazer um busca com hashing, cria a tabela de hashing
        tabela_hash = criar_hash_table(datas_n, n);
    }

    //Testar se o algoritmo de ordenação hierárquico estava funcionando
    // for(int i = 0; i < n; i++) {
    //     printf("%d %d %d / ", datas_n[i].dia, datas_n[i].mes, datas_n[i].ano);
    // } 
    // printf("\n");

    bool encontrada;
    for(i = 0; i < q; i++) {
        //Para cada uma das Q datas, verifica se foi encontrada entre as N
        encontrada = buscar_data(datas_n, datas_q[i], n, metodo, tabela_hash);

        encontrada ? printf("ENCONTRADA\n") : printf("NAO_ENCONTRADA\n");
    }

    //Caso tenha feito busca com hashing, desaloca a tabela de hashing e cada uma das listas dos buckets
    if(metodo == 2) {
        for(int i = 0; i < 2 * n; i++) {
            if(tabela_hash[i] != NULL) {
                NO *atual = tabela_hash[i]->inicio;
                while(atual != NULL) {
                    NO *temp = atual;
                    atual = atual->proximo;
                    free(temp);
                }
                free(tabela_hash[i]);
            }
        }

        free(tabela_hash);
    }

    //Desaloca o vetor das N e das Q datas
    free(datas_n);
    free(datas_q);
    
    return 0;
}