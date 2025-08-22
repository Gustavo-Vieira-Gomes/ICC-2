#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Lê uma linha de qualquer tamanho (sem o '\n'). Retorna NULL no EOF sem dados. */
static char *read_line(void) {
    int c;
    size_t cap = 128, len = 0;
    char *buf = malloc(cap);
    if (!buf) return NULL;

    while ((c = getchar()) != EOF) {
        if (c == '\r') continue;          /* ignora CR (Windows) */
        if (c == '\n') break;             /* fim da linha */
        if (len + 1 >= cap) {
            cap *= 2;
            char *tmp = realloc(buf, cap);
            if (!tmp) { free(buf); return NULL; }
            buf = tmp;
        }
        buf[len++] = (char)c;
    }

    if (c == EOF && len == 0) {           /* EOF sem dados */
        free(buf);
        return NULL;
    }

    buf[len] = '\0';
    return buf;
}

/* Verifica palíndromo ignorando não-alfanuméricos e caixa. */
static int is_palindrome(const char *s) {
    size_t i = 0, j = strlen(s);
    if (j == 0) return 1;                 /* linha vazia conta como palíndroma */
    j--;                                  /* último índice válido */

    while (i < j) {
        while (i < j && !isalnum((unsigned char)s[i])) i++;
        while (i < j && !isalnum((unsigned char)s[j])) j--;
        if (i >= j) break;

        unsigned char a = (unsigned char)s[i];
        unsigned char b = (unsigned char)s[j];
        a = (unsigned char)tolower(a);
        b = (unsigned char)tolower(b);

        if (a != b) return 0;
        i++; j--;
    }
    return 1;
}

int main(void) {
    char *line;
    while ((line = read_line()) != NULL) {
        puts(is_palindrome(line) ? "Sim" : "Não");
        free(line);
    }
    return 0;
}
