// Gustavo Vieira Gomes - N° USP: 16907251
// André Campanholo Paschoalini - N° USP: 14558061

#include "stdio.h"

// Nosso Código
int potencia(int n, int k) {
    if (k == 0) return 1;

    if (k == 1) return n % 1000;

    if (k%2 == 0) {
        return ((potencia(n, k/2) % 1000) * (potencia(n, k/2) % 1000)) % 1000;
    }

    return ((potencia(n, k/2) % 1000) * (potencia(n, k/2) % 1000 ) * (n % 1000)) % 1000;
}

int main() {
    int n, k;

    scanf("%d %d", &n, &k);

    int resultado = potencia(n, k);

    printf("%d", resultado);

    return 0;
}