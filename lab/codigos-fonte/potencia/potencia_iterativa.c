#include <stdio.h>
#include <math.h>

int main() {
    int n, k, potencia = 1;
    scanf("%d %d", &n, &k);

    for(int i = 1; i <= k; i++) {
        potencia = (potencia * n) % 1000;
    }

    printf("%d\n", potencia);

    return 0;
}