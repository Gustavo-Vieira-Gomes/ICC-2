#include "stdio.h"

int potencia(int n, int k) {
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