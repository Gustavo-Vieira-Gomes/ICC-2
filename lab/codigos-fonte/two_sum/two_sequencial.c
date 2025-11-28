//André Campanholo Paschoalini - 14558061
//Gustavo Vieira Gomes - 16907251

#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M;
    scanf("%d", &N);
    int *array = (int *)malloc(N * sizeof(int));

    for(int i = 0; i < N; i++) {
        scanf("%d", &array[i]);
    }

    scanf("%d", &M);

    int procurado;
    for(int i = 0; i < M; i++) {
        scanf("%d", &procurado);
        int encontrou = 0;
        for(int j = 0; j < N - 1; j++) {
            for(int k = j + 1; k < N; k++) {
                if(array[j] + array[k] == procurado) {
                    encontrou = 1;
                    break;
                }
            }
            if(encontrou) break;
        }
        if(encontrou) printf("S\n");
        else printf("N\n");
    }

    free(array);

    return 0;
}