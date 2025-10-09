#include <stdio.h>
#include <stdlib.h>

typedef struct { 
    int peso; 
    int valor; 
} Item;


// ==================== FORÇA BRUTA ====================
int forca_bruta(Item* itens, int n, int capacidade) {
    int melhor_valor = 0;
    
    // Testa todas as 2^n combinações possíveis
    for (int i = 0; i < (1 << n); i++) {
        int peso_total = 0;
        int valor_total = 0;
        
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {  // Se o item j está na combinação
                peso_total += itens[j].peso;
                valor_total += itens[j].valor;
            }
        }
        
        // Se cabe na mochila e tem valor melhor
        if (peso_total <= capacidade && valor_total > melhor_valor) {
            melhor_valor = valor_total;
        }
    }
    
    return melhor_valor;
}

// ==================== ALGORITMO GULOSO ====================

// Função para calcular razão valor/peso
double calcular_razao(Item item) {
    return (double)item.valor / (double)item.peso;
}

// Função para trocar dois itens
void trocar_itens(Item* a, Item* b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

// Função de ordenação (Bubble Sort por razão valor/peso)
void ordenar_por_razao(Item* itens, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            double razao1 = calcular_razao(itens[j]);
            double razao2 = calcular_razao(itens[j + 1]);
            
            // Se a razão do item j for menor que a do item j+1, troca
            if (razao1 < razao2) {
                trocar_itens(&itens[j], &itens[j + 1]);
            }
        }
    }
}
int algoritmo_guloso(Item* itens, int n, int capacidade) {
    // Ordena os itens por razão valor/peso (maior primeiro)
    ordenar_por_razao(itens, n);
    
    int peso_total = 0;
    int valor_total = 0;
    
    // Pega os itens na ordem da razão, enquanto couber
    for (int i = 0; i < n; i++) {
        if (peso_total + itens[i].peso <= capacidade) {
            peso_total += itens[i].peso;
            valor_total += itens[i].valor;
        }
    }
    
    return valor_total;
}

// ==================== PROGRAMAÇÃO DINÂMICA ====================
int programacao_dinamica(Item* itens, int n, int capacidade) {
    // Cria tabela DP: dp[w] = melhor valor com capacidade w
    int* dp = (int*)calloc(capacidade + 1, sizeof(int));
    
    // Para cada item
    for (int i = 0; i < n; i++) {
        // Para cada capacidade (de trás para frente para evitar usar o mesmo item duas vezes)
        for (int w = capacidade; w >= itens[i].peso; w--) {
            // Escolhe o melhor: não pegar o item ou pegar o item
            int pegar = dp[w - itens[i].peso] + itens[i].valor;
            if (pegar > dp[w]) {
                dp[w] = pegar;
            }
        }
    }
    
    int resultado = dp[capacidade];
    free(dp);
    return resultado;
}

// ==================== FUNÇÕES AUXILIARES ====================

// Lê os dados do usuário
void ler_dados(Item** itens, int* n, int* capacidade) {
    printf("Digite o número de itens: ");
    scanf("%d", n);
    
    printf("Digite a capacidade da mochila: ");
    scanf("%d", capacidade);
    
    *itens = (Item*)malloc(*n * sizeof(Item));
    
    printf("\nDigite peso e valor de cada item:\n");
    for (int i = 0; i < *n; i++) {
        printf("Item %d (peso valor): ", i + 1);
        scanf("%d %d", &(*itens)[i].peso, &(*itens)[i].valor);
    }
}

// Exibe o menu de opções
void exibir_menu() {
    printf("\n=== PROBLEMA DA MOCHILA 0/1 ===\n");
    printf("Escolha o método:\n");
    printf("1. Força Bruta\n");
    printf("2. Algoritmo Guloso\n");
    printf("3. Programação Dinâmica\n");
    printf("4. Comparar todos os métodos\n");
    printf("0. Sair\n");
    printf("Opção: ");
}

// ==================== FUNÇÃO PRINCIPAL ====================
int main() {
    Item* itens;
    int n, capacidade;
    int opcao;
    
    // Lê os dados
    ler_dados(&itens, &n, &capacidade);
    
    do {
        exibir_menu();
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: {
                printf("\n--- FORÇA BRUTA ---\n");
                int resultado = forca_bruta(itens, n, capacidade);
                printf("Melhor valor: %d\n", resultado);
                break;
            }
            case 2: {
                printf("\n--- ALGORITMO GULOSO ---\n");
                int resultado = algoritmo_guloso(itens, n, capacidade);
                printf("Melhor valor: %d\n", resultado);
                break;
            }
            case 3: {
                printf("\n--- PROGRAMAÇÃO DINÂMICA ---\n");
                int resultado = programacao_dinamica(itens, n, capacidade);
                printf("Melhor valor: %d\n", resultado);
                break;
            }
            case 4: {
                printf("\n--- COMPARAÇÃO DE MÉTODOS ---\n");
                
                printf("Força Bruta: %d\n", forca_bruta(itens, n, capacidade));
                printf("Algoritmo Guloso: %d\n", algoritmo_guloso(itens, n, capacidade));
                printf("Programação Dinâmica: %d\n", programacao_dinamica(itens, n, capacidade));
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    
    free(itens);
    return 0;
}
