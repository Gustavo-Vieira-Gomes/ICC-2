#include "stdio.h"

// IA
int potencia_iterativa(int n, int k) {
    int resultado = 1;
    int base = n % 1000;
    
    while (k > 0) {
        if (k % 2 == 1) {
            resultado = (resultado * base) % 1000;
        }
        base = (base * base) % 1000;
        k = k / 2;
    }
    
    return resultado;
}

int main() {
    int n, k;

    scanf("%d %d", &n, &k);

    int resultado = potencia_iterativa(n, k);

    printf("%d", resultado);

    return 0;
}
