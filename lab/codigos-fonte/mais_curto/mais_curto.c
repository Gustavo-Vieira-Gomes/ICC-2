#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct data DATA;
struct data {
    int dia;
    int mes;
    int ano;
};

void swap_datas(DATA *a, DATA *b) {
    DATA temp = *a;
    *a = *b;
    *b = temp;
}

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

void ordenar_datas(DATA *datas_n, int n) {
    quick_sort_anos(datas_n, 0, n - 1);
    
    int i = 0; 
    while(i < n) {
        int ano = datas_n[i].ano, j = i + 1;
        while(j < n && datas_n[j].ano == ano) {
            j++;
        }
        if(j != i + 1) {
            quick_sort_meses(datas_n, i, j - 1);

            int k = i;
            while(k < j) {
                int mes = datas_n[k].mes, h = k + 1;
                while(h < j && datas_n[h].mes == mes) {
                    h++;
                }
                if(h != k + 1) {
                    quick_sort_dias(datas_n, k, h - 1);
                }
                k = h;
            }
        }
        i = j;
    }
}

bool busca_binaria(DATA *datas_n, int ini, int fim, DATA data_q) {
    if(ini > fim) return false;
    
    int meio = (fim + ini) / 2;

    if(data_q.ano == datas_n[meio].ano &&
        data_q.mes == datas_n[meio].mes &&
        data_q.dia == datas_n[meio].dia) {

        return true;

    } else if(data_q.ano < datas_n[meio].ano ||
        data_q.ano == datas_n[meio].ano && data_q.mes < datas_n[meio].mes ||
        data_q.ano == datas_n[meio].ano && data_q.mes == datas_n[meio].mes && data_q.dia < datas_n[meio].dia) {

        return busca_binaria(datas_n, ini, meio - 1, data_q);

    } else if(data_q.ano > datas_n[meio].ano ||
        data_q.ano == datas_n[meio].ano && data_q.mes > datas_n[meio].mes ||
        data_q.ano == datas_n[meio].ano && data_q.mes == datas_n[meio].mes && data_q.dia > datas_n[meio].dia) {

        return busca_binaria(datas_n, meio + 1, fim, data_q);
    }

    return false;
}

DATA **criar_tabela_hash_datas(DATA *datas_n, int n) {
    DATA **tabela_hash = (DATA **)malloc(5 * n * sizeof(DATA *));
    for(int i = 0; i < 5 * n; i++) {
        tabela_hash[i] = NULL;
    }

    //Função de Hashing: h(k) = Sk % n, onde Sk é a soma do dia, do mes e do ano de k;
    for(int i = 0; i < n; i++) {
        int indice = (datas_n[i].dia + datas_n[i].mes + datas_n[i].ano) % (5 * n);

        if(tabela_hash[indice] == NULL) {
            tabela_hash[indice] = &(datas_n[i]);

        } else {
            //Função de ReHashing (Sondagem Linear): Soma incrementa o indice em 1 enquanto não encontrar um bucket vazio;
            while(tabela_hash[indice] != NULL) {
                indice = (indice + 1) % (5 * n);
            }

            tabela_hash[indice] = &(datas_n[i]);
        }
    }

    return tabela_hash;
}

bool busca_hashing(DATA *datas_n, DATA data_q, DATA **tabela_hash, int n) {
    int indice_q = (data_q.dia + data_q.mes + data_q.ano) % (5 * n);
    int indice_original = indice_q;
    
    do {
        if(tabela_hash[indice_q] == NULL) {
            return false;
        }
        
        if(tabela_hash[indice_q]->ano == data_q.ano && 
           tabela_hash[indice_q]->mes == data_q.mes && 
           tabela_hash[indice_q]->dia == data_q.dia) {
            return true;
        }
        
        indice_q = (indice_q + 1) % (5 * n);

    } while(indice_q != indice_original);
    
    return false;
}

bool busca_sequencial(DATA *datas_n, DATA data_q, int n) {
    for(int i = 0; i < n; i++) {
        if(data_q.ano == datas_n[i].ano && data_q.mes == datas_n[i].mes && data_q.dia == datas_n[i].dia) {
            return true;
        }
    }
    return false;
}

bool buscar_data(DATA *datas_n, DATA data_q, int n, int metodo) {
    switch(metodo) {
        case 1:
            return busca_binaria(datas_n, 0, n - 1, data_q);
            break;

        case 2:
            DATA **tabela_hash = criar_tabela_hash_datas(datas_n, n);
            bool encontrou = busca_hashing(datas_n, data_q, tabela_hash, n);

            free(tabela_hash);

            return encontrou;
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
    DATA *datas_n = (DATA *)malloc(n * sizeof(DATA));

    int i = 0;
    while(i < n) {
        scanf("%d-%d-%d", &datas_n[i].dia, &datas_n[i].mes, &datas_n[i].ano);
        i++;
    }

    int q;
    scanf("%d", &q);
    DATA *datas_q = (DATA *)malloc(q * sizeof(DATA));

    i = 0;
    while(i < q) {
        scanf("%d-%d-%d", &datas_q[i].dia, &datas_q[i].mes, &datas_q[i].ano);
        i++;
    }

    int metodo;
    scanf("%d", &metodo);
    if(metodo == 1) {
        ordenar_datas(datas_n, n);
    }

    // for(int i = 0; i < n; i++) {
    //     printf("%d %d %d / ", datas_n[i].dia, datas_n[i].mes, datas_n[i].ano);
    // } 
    // printf("\n");

    bool encontrada;
    for(i = 0; i < q; i++) {
        encontrada = buscar_data(datas_n, datas_q[i], n, metodo);

        encontrada ? printf("ENCONTRADA\n") : printf("NAO_ENCONTRADA\n");
    }

    free(datas_n);
    free(datas_q);
    
    return 0;
}