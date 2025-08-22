#include <stdio.h>

int mdc(int n1, int n2) {
    if (n2 == 0 && n1 !=0) return n1
    if (n2 != 0 && n1 == 0) return n2

    return mdc(n2, (n1%n2))
}

int main() {
    int number, number2, mdc;

    scanf("%d %d", &number, &number2);

    mdc = mdc(number, number2);

    printf("%d", mdc);


    return 0;

}