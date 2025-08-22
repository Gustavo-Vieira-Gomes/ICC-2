# Palindromo - Atividade 1

## Problema

O objetivo da atividade é receber uma série de linhas, até EOF, e verificar se cada linha é ou não um palíndromo. As linhas de entrada podem conter uma palavra, uma frase, e caracteres alfanuméricos ou não-alfanuméricos.
Três soluções deviam ser criadas: Uma recursiva feita por nós, uma recursiva feita pela IA e uma iterativa feita por nós.

### Comparação entre versão Iterativa feita por nós x feita pela IA

#### Entrada de dados:

Enquanto nós alocamos uma quantidade inicial de memória, definindo um tamanho limite para as strings, e fizemos a leitura da linha por completo, usando o fgets. Já a IA criou uma função auxiliar para ler uma linha, a qual utilizou 

```c
// Nossa versão
char *palavra;
    palavra = (char *)malloc(1000 * sizeof(char));

    // Lê uma linha de qualquer tamanho (sem o '\n'). Retorna NULL no EOF sem dados.
    while (fgets(palavra, 999, stdin) != NULL) {...}
```

```c
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
```
